/*
Game Manager - Handles all game logic, state management, and orchestration
This file manages:
- Main game loop and flow control
- Scoring system and level progression  
- Game over detection and handling
- Line clearing mechanics
- Game state initialization and cleanup
- Integration between assets, rendering, and input systems

This separates game management from asset-specific operations.
*/

#include "game_manager.h"
#include "asset_manager.h"
#include "../render/render.h"
#include "../input/input.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Initialize game state
void initialize_game(struct RenderContext* ctx) {
    // Initialize the board for tracking landed pieces
    init_board(ctx);
    
    // Initialize score system
    ctx->score = 0;
    ctx->lines_cleared_total = 0;
    ctx->level = 0;
}

// Clean up game resources
void cleanup_game(struct RenderContext* ctx) {
    free_board(ctx);
}

// Update score and level based on lines cleared
void update_score_and_level(struct RenderContext* ctx, int lines_cleared) {
    if (lines_cleared > 0) {
        ctx->lines_cleared_total += lines_cleared;
        
        // Scoring system: 1 line = 100, 2 lines = 300, 3 lines = 500, 4 lines = 800
        int points[] = {0, 100, 300, 500, 800};
        ctx->score += points[lines_cleared < 4 ? lines_cleared : 4] * (ctx->level + 1);
        
        // Increase level every 5 lines (was 10) for faster progression
        ctx->level = ctx->lines_cleared_total / 5;
    }
}

// Clear completed lines and return number of lines cleared
int clear_lines(struct RenderContext* ctx) {
    int lines_cleared = 0;
    
    // Check each row from bottom to top
    for (int y = ctx->height - 1; y >= 0; y--) {
        int line_complete = 1;
        
        // Check if this line is completely filled
        for (int x = 0; x < ctx->width; x++) {
            if (ctx->board[y][x] != 1) {
                line_complete = 0;
                break;
            }
        }
        
        // If line is complete, clear it and shift everything down
        if (line_complete) {
            lines_cleared++;
            
            // Shift all lines above this one down by one
            for (int shift_y = y; shift_y > 0; shift_y--) {
                for (int x = 0; x < ctx->width; x++) {
                    ctx->board[shift_y][x] = ctx->board[shift_y - 1][x];
                }
            }
            
            // Clear the top line
            for (int x = 0; x < ctx->width; x++) {
                ctx->board[0][x] = 0;
            }
            
            // Check this row again since we shifted everything down
            y++;
        }
    }
    
    // Update score and level
    update_score_and_level(ctx, lines_cleared);
    
    return lines_cleared;
}

// Check if game is over (pieces reached the top)
int is_game_over(struct RenderContext* ctx, struct TetrisAsset* asset) {
    // Check if the newly spawned asset immediately collides (can't be placed)
    if (asset && check_asset_collision(asset, ctx)) {
        return 1;  // Game over - new piece can't be placed
    }
    
    // Alternative check: if top rows have pieces, it's getting dangerous
    for (int y = 0; y < 3; y++) {  // Check top 3 rows
        for (int x = 0; x < ctx->width; x++) {
            if (ctx->board[y][x] == 1) {
                // If we're at the very top, it's game over
                if (y == 0) return 1;
            }
        }
    }
    
    return 0;  // Game continues
}

// Main game manager that handles continuous asset spawning and game flow
void run_tetris_game(struct RenderContext* ctx, unsigned int refresh_rate) {
    struct TetrisAsset* current_asset = NULL;
    int game_running = 1;
    
    // Lock delay variables - simplified for quick adjustments only
    int lock_delay_moves_allowed = 2; // Allow only 2 moves after landing
    int lock_delay_moves_used = 0;
    int is_in_lock_delay = 0;
    
    // Initialize game state
    initialize_game(ctx);
    
    printf("🎮 Tetris Game Starting!\n");
    printf("Controls: ← → ↓ (movement), ↑ (rotate), q (quit)\n\n");
    
    while (game_running) {
        // Spawn new asset if none exists
        if (current_asset == NULL) {
            unsigned char asset_id = random_asset();
            current_asset = spawn_asset(asset_id, ctx);
            
            // Reset lock delay state for new piece
            is_in_lock_delay = 0;
            lock_delay_moves_used = 0;
            
            // Check for game over immediately after spawning
            if (is_game_over(ctx, current_asset)) {
                printf("\n🎮 GAME OVER! 🎮\n");
                printf("Final Score: %d\n", ctx->score);
                printf("Level Reached: %d\n", ctx->level);
                printf("Lines Cleared: %d\n", ctx->lines_cleared_total);
                printf("\nPress any key to exit...\n");
                get_single_input();
                game_running = 0;
                break;
            }
        }
        
        // Game loop for current asset
        int fall_counter = 0;
        // Aggressive speed progression: starts very fast and gets even faster
        int fall_speed = 6 - (ctx->level * 2);  // Starts at 6, decreases by 2 per level
        if (fall_speed < 1) fall_speed = 1;  // Minimum speed (very fast!)
        
        while (current_asset) {
            // Check if asset has landed
            int has_landed = has_asset_landed(current_asset, ctx);
            
            // Handle lock delay logic - simplified move-based system
            if (has_landed && !is_in_lock_delay) {
                // Asset just landed - start lock delay
                is_in_lock_delay = 1;
                lock_delay_moves_used = 0;
            } else if (has_landed && is_in_lock_delay) {
                // Asset is in lock delay - check if moves exhausted
                if (lock_delay_moves_used >= lock_delay_moves_allowed) {
                    // Used up allowed moves - lock the piece
                    break;
                }
            } else if (!has_landed && is_in_lock_delay) {
                // Asset moved away from landing position - cancel lock delay
                is_in_lock_delay = 0;
                lock_delay_moves_used = 0;
            }
            
            // Check for player input
            char input = get_single_input();
            if (input != 0) {
                if (input == 'Q' || input == 'q') {
                    printf("\nGame ended by player.\n");
                    game_running = 0;
                    break;
                }
                // Move asset based on input (allowed even during lock delay)
                unsigned char move_result = manage_asset(input, current_asset, ctx);
                
                // Check for hard drop signal (down arrow on landed piece)
                if (move_result == 1) {
                    // Hard drop - instantly lock the piece
                    break;
                }
                
                // If piece moved during lock delay, count the move
                if (is_in_lock_delay) {
                    lock_delay_moves_used++;
                }
            }
            
            // Make asset fall automatically (only if not in lock delay)
            if (!is_in_lock_delay) {
                fall_counter++;
                if (fall_counter >= fall_speed) {
                    current_asset->y++;  // Move asset down one row
                    fall_counter = 0;
                }
            }
            
            // Render current frame
            render_frame_with_asset(ctx, current_asset);
            usleep(refresh_rate * 1000);  // Control animation speed
        }
        
        // Asset has landed - lock it to the board and prepare for next
        if (current_asset) {
            lock_asset_to_board(ctx, current_asset);  // Lock the asset to the board
            free_asset(current_asset);
            current_asset = NULL;
            
            // Check for and clear completed lines
            int lines_cleared = clear_lines(ctx);
            
            // Shorter pause, and even shorter if lines were cleared (for smoother flow)
            usleep(lines_cleared > 0 ? 50000 : 30000); // 0.05s if lines cleared, 0.03s otherwise
        }
    }
    
    // Clean up when game ends
    cleanup_game(ctx);
    printf("Game Over!\n");
}
