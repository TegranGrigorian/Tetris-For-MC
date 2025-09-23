

#include "game_manager.h"
#include "asset_manager.h"
#include "../render/render.h"
#include "../input/input.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void initialize_game(struct RenderContext* ctx) {
    init_board(ctx);
    ctx->score = 0;
    ctx->lines_cleared_total = 0;
    ctx->level = 0;
}

void cleanup_game(struct RenderContext* ctx) {
    free_board(ctx);
}

void update_score_and_level(struct RenderContext* ctx, int lines_cleared) {
    if (lines_cleared > 0) {
        ctx->lines_cleared_total += lines_cleared;
        int points[] = {0, 100, 300, 500, 800};
        ctx->score += points[lines_cleared < 4 ? lines_cleared : 4] * (ctx->level + 1);
        ctx->level = ctx->lines_cleared_total / 5;
    }
}

int clear_lines(struct RenderContext* ctx) {
    int lines_cleared = 0;
    
    for (int y = ctx->height - 1; y >= 0; y--) {
        int line_complete = 1;
        
        for (int x = 0; x < ctx->width; x++) {
            if (ctx->board[y][x] != 1) {
                line_complete = 0;
                break;
            }
        }
        
        if (line_complete) {
            lines_cleared++;
            
            for (int shift_y = y; shift_y > 0; shift_y--) {
                for (int x = 0; x < ctx->width; x++) {
                    ctx->board[shift_y][x] = ctx->board[shift_y - 1][x];
                }
            }
            
            for (int x = 0; x < ctx->width; x++) {
                ctx->board[0][x] = 0;
            }
            
            y++;
        }
    }
    
    update_score_and_level(ctx, lines_cleared);
    
    return lines_cleared;
}

int is_game_over(struct RenderContext* ctx, struct TetrisAsset* asset) {
    if (asset && check_asset_collision(asset, ctx)) {
        return 1;
    }
    
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < ctx->width; x++) {
            if (ctx->board[y][x] == 1) {
                if (y == 0) return 1;
            }
        }
    }
    
    return 0;
}

void run_tetris_game(struct RenderContext* ctx, unsigned int refresh_rate) {
    struct TetrisAsset* current_asset = NULL;
    int game_running = 1;
    
    int lock_delay_moves_allowed = 2;
    int lock_delay_moves_used = 0;
    int is_in_lock_delay = 0;
    
    initialize_game(ctx);
    
    printf("Tetris Game Starting!\n");
    printf("Controls: ← → ↓ (movement), ↑ (rotate), q (quit)\n\n");
    
    while (game_running) {
        if (current_asset == NULL) {
            unsigned char asset_id = random_asset();
            current_asset = spawn_asset(asset_id, ctx);
            
            is_in_lock_delay = 0;
            lock_delay_moves_used = 0;
            
            if (is_game_over(ctx, current_asset)) {
                printf("\nGAME OVER!\n");
                printf("Final Score: %d\n", ctx->score);
                printf("Level Reached: %d\n", ctx->level);
                printf("Lines Cleared: %d\n", ctx->lines_cleared_total);
                printf("\nPress 'r' to restart or 'q' to quit: ");
                
                char choice;
                do {
                    choice = get_single_input();
                } while (choice != 'r' && choice != 'R' && choice != 'q' && choice != 'Q');
                
                if (choice == 'r' || choice == 'R') {
                    cleanup_game(ctx);
                    initialize_game(ctx);
                    if (current_asset) {
                        free_asset(current_asset);
                        current_asset = NULL;
                    }
                    continue;
                } else {
                    game_running = 0;
                    break;
                }
            }
        }
        
        int fall_counter = 0;
        int fall_speed = 6 - (ctx->level * 2);
        if (fall_speed < 1) fall_speed = 1;
        
        while (current_asset) {
            int has_landed = has_asset_landed(current_asset, ctx);
            
            if (has_landed && !is_in_lock_delay) {
                is_in_lock_delay = 1;
                lock_delay_moves_used = 0;
            } else if (has_landed && is_in_lock_delay) {
                if (lock_delay_moves_used >= lock_delay_moves_allowed) {
                    break;
                }
            } else if (!has_landed && is_in_lock_delay) {
                is_in_lock_delay = 0;
                lock_delay_moves_used = 0;
            }
            
            char input = get_single_input();
            if (input != 0) {
                if (input == 'Q' || input == 'q') {
                    printf("\nGame ended by player.\n");
                    game_running = 0;
                    break;
                }
                unsigned char move_result = manage_asset(input, current_asset, ctx);
                
                if (move_result == 1) {
                    break;
                }
                
                if (is_in_lock_delay) {
                    lock_delay_moves_used++;
                }
            }
            
            if (!is_in_lock_delay) {
                fall_counter++;
                if (fall_counter >= fall_speed) {
                    current_asset->y++;
                    fall_counter = 0;
                }
            }
            
            render_frame_with_asset(ctx, current_asset);
            usleep(refresh_rate * 1000);
        }
        
        if (current_asset) {
            lock_asset_to_board(ctx, current_asset);
            free_asset(current_asset);
            current_asset = NULL;
            
            int lines_cleared = clear_lines(ctx);
            
            usleep(lines_cleared > 0 ? 50000 : 30000);
        }
    }
    
    cleanup_game(ctx);
    printf("Game Over!\n");
}
