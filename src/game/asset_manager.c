/*
This file will act like a manager of all the assets, it will run the functions from the other asset files that
// Check if asset has landed (hit bottom or another asset)
int has_asset_landed(struct TetrisAsset* asset, struct RenderContext* ctx) {
    // Check if asset hit the bottom
    if (asset->y + asset->height >= ctx->height) {
        return 1;
    }
    
    // Check collision with landed pieces on the board
    for (int y = 0; y < asset->height; y++) {
        for (int x = 0; x < asset->width; x++) {
            if (asset->shape[y][x] == '#') {
                int board_x = asset->x + x;
                int board_y = asset->y + y + 1;  // Check position below
                
                // Make sure we're within bounds
                if (board_x >= 0 && board_x < ctx->width && 
                    board_y >= 0 && board_y < ctx->height) {
                    // Check if there's a landed piece below this block
                    if (ctx->board[board_y][board_x] == 1) {
                        return 1;  // Collision with landed piece
                    }
                }
            }
        }
    }
    
    return 0; // Asset is still falling
}y for the game to run.
Example:
Random asset spawning
    * Spawn a random asset
Moving asset given an input
    * Move asset left, right, down, rotate
Collision detection
    * Check if asset collides with walls or other assets
    * Lock asset in place if it collides while falling
Line clearing
    * Check for and clear completed lines
    * Update score and level
This file wont do anything else for the game managment, that will be done in the main game loop in main.c
*/

#include "asset_manager.h"
#include "../render/render.h"
#include "../input/input.h"
#include "../assets/cube.h"
#include "../assets/line.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
struct TetrisAsset* spawn_asset(unsigned char asset_id, struct RenderContext* ctx) {
    struct TetrisAsset* new_asset = NULL;
    int spawn_x = ctx->width / 2; // Spawn at center top
    int spawn_y = 0; // Spawn at top
    
    switch (asset_id) {
        case 0: // spawn cube
            new_asset = create_cube_asset(spawn_x - 1, spawn_y); // Center 2x2 cube
            break;
        case 1: // spawn line
            new_asset = create_line_asset(spawn_x, spawn_y); // Center 1x4 line
            break;
        case 2: // spawn L piece
            // TODO: implement L piece when created
            new_asset = create_cube_asset(spawn_x - 1, spawn_y); // Fallback to cube
            break;
        case 3: // spawn T piece
            // TODO: implement T piece when created
            new_asset = create_cube_asset(spawn_x - 1, spawn_y); // Fallback to cube
            break;
        case 4: // spawn S piece
            // TODO: implement S piece when created
            new_asset = create_cube_asset(spawn_x - 1, spawn_y); // Fallback to cube
            break;
        case 5: // spawn Z piece
            // TODO: implement Z piece when created
            new_asset = create_cube_asset(spawn_x - 1, spawn_y); // Fallback to cube
            break;
        case 6: // spawn J piece
            // TODO: implement J piece when created
            new_asset = create_cube_asset(spawn_x - 1, spawn_y); // Fallback to cube
            break;
        default:
            printf("ERROR: Invalid asset ID %d\n", asset_id);
            new_asset = create_cube_asset(spawn_x - 1, spawn_y); // Fallback to cube
            break;
    }
    
    return new_asset;
}

unsigned char random_asset() {
    // Initialize random seed if not already done
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    
    // picks a random asset, currently only 2 types (cube=0, line=1)
    // Will expand to 7 total when more pieces are implemented
    return rand() % 2;  // Only cube and line for now
}

unsigned char manage_asset(unsigned char input, struct TetrisAsset* asset, struct RenderContext* ctx) {
    // manage asset movement and rotation based on input
    switch (input) {
        case 3: // Left Arrow
            if (asset->x > 0) {  // Check left boundary
                int old_x = asset->x;
                asset->x--;
                
                // Check for collision with landed pieces
                if (check_asset_collision(asset, ctx)) {
                    asset->x = old_x;  // Revert movement
                }
            }
            break;
        case 4: // Right Arrow
            if (asset->x + asset->width < ctx->width) {  // Check right boundary
                int old_x = asset->x;
                asset->x++;
                
                // Check for collision with landed pieces
                if (check_asset_collision(asset, ctx)) {
                    asset->x = old_x;  // Revert movement
                }
            }
            break;
        case 2: // Down Arrow
            if (asset->y + asset->height < ctx->height) {  // Check bottom boundary
                int old_y = asset->y;
                asset->y++;
                
                // Check for collision with landed pieces
                if (check_asset_collision(asset, ctx)) {
                    asset->y = old_y;  // Revert movement
                }
            }
            break;
        case 1: // Up Arrow (rotate)
            {
                // Store original dimensions and shape
                int old_width = asset->width;
                int old_height = asset->height;
                char** old_shape = asset->shape;
                
                // Create backup of shape
                char** backup_shape = malloc(old_height * sizeof(char*));
                for (int i = 0; i < old_height; i++) {
                    backup_shape[i] = malloc((old_width + 1) * sizeof(char));
                    strcpy(backup_shape[i], old_shape[i]);
                }
                
                // Attempt rotation
                rotate_asset(asset);
                
                // Check if rotation is valid (within bounds and no collision)
                if (asset->x + asset->width > ctx->width || 
                    asset->y + asset->height > ctx->height ||
                    check_asset_collision(asset, ctx)) {
                    
                    // Rotation failed - revert to original
                    for (int i = 0; i < asset->height; i++) {
                        free(asset->shape[i]);
                    }
                    free(asset->shape);
                    
                    asset->shape = backup_shape;
                    asset->width = old_width;
                    asset->height = old_height;
                } else {
                    // Rotation succeeded - free backup
                    for (int i = 0; i < old_height; i++) {
                        free(backup_shape[i]);
                    }
                    free(backup_shape);
                }
            }
            break;
        default:
            // No action for other inputs
            break;
    }
    return 0; // return 0 for success, can be expanded for error handling
}

void check_collision(struct TetrisAsset* asset) {
    // check for collisions with walls or other assets
    // if collision detected, revert asset position or lock in place
}

// Check if asset collides with landed pieces on the board
int check_asset_collision(struct TetrisAsset* asset, struct RenderContext* ctx) {
    for (int y = 0; y < asset->height; y++) {
        for (int x = 0; x < asset->width; x++) {
            if (asset->shape[y][x] == '#') {
                int board_x = asset->x + x;
                int board_y = asset->y + y;
                
                // Check if position is within bounds and occupied on board
                if (board_x >= 0 && board_x < ctx->width && 
                    board_y >= 0 && board_y < ctx->height) {
                    if (ctx->board[board_y][board_x] == 1) {
                        return 1;  // Collision detected
                    }
                }
            }
        }
    }
    return 0;  // No collision
}

// Check if asset has landed (hit bottom or another asset)
int has_asset_landed(struct TetrisAsset* asset, struct RenderContext* ctx) {
    // Check if asset hit the bottom
    if (asset->y + asset->height >= ctx->height) {
        return 1; // Asset has landed
    }
    
    // Check collision with landed pieces on the board (one position below)
    for (int y = 0; y < asset->height; y++) {
        for (int x = 0; x < asset->width; x++) {
            if (asset->shape[y][x] == '#') {
                int board_x = asset->x + x;
                int board_y = asset->y + y + 1;  // Check position below this block
                
                // Make sure we're within bounds
                if (board_x >= 0 && board_x < ctx->width && 
                    board_y >= 0 && board_y < ctx->height) {
                    // Check if there's a landed piece below this block
                    if (ctx->board[board_y][board_x] == 1) {
                        return 1;  // Asset has landed on another piece
                    }
                }
            }
        }
    }
    
    return 0; // Asset is still falling
}

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
    
    // Update score and level based on lines cleared
    if (lines_cleared > 0) {
        ctx->lines_cleared_total += lines_cleared;
        
        // Scoring system: 1 line = 100, 2 lines = 300, 3 lines = 500, 4 lines = 800
        int points[] = {0, 100, 300, 500, 800};
        ctx->score += points[lines_cleared < 4 ? lines_cleared : 4] * (ctx->level + 1);
        
        // Increase level every 10 lines
        ctx->level = ctx->lines_cleared_total / 10;
    }
    
    return lines_cleared;
}

// Game manager that handles continuous asset spawning
void run_tetris_game(struct RenderContext* ctx, unsigned int refresh_rate) {
    struct TetrisAsset* current_asset = NULL;
    int game_running = 1;
    
    // Initialize the board for tracking landed pieces
    init_board(ctx);
    
    // Initialize score system
    ctx->score = 0;
    ctx->lines_cleared_total = 0;
    ctx->level = 0;
    
    printf("🎮 Tetris Game Starting!\n");
    printf("Controls: ← → ↓ (movement), ↑ (rotate), q (quit)\n\n");
    
    while (game_running) {
        // Spawn new asset if none exists
        if (current_asset == NULL) {
            unsigned char asset_id = random_asset();
            current_asset = spawn_asset(asset_id, ctx);
        }
        
        // Game loop for current asset
        int fall_counter = 0;
        // Dynamic speed: starts faster and increases with level
        int fall_speed = 8 - ctx->level;  // Starts at 8, decreases with level (min 1)
        if (fall_speed < 1) fall_speed = 1;  // Minimum speed
        
        while (current_asset && !has_asset_landed(current_asset, ctx)) {
            // Check for player input
            char input = get_single_input();
            if (input != 0) {
                if (input == 'Q' || input == 'q') {
                    printf("\nGame ended by player.\n");
                    game_running = 0;
                    break;
                }
                // Move asset based on input
                manage_asset(input, current_asset, ctx);
            }
            
            // Make asset fall automatically
            fall_counter++;
            if (fall_counter >= fall_speed) {
                current_asset->y++;  // Move asset down one row
                fall_counter = 0;
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
            
            // Shorter pause, and even shorter if lines were cleared (for better flow)
            usleep(lines_cleared > 0 ? 200000 : 100000); // 0.2s if lines cleared, 0.1s otherwise
        }
    }
    
    // Clean up the board when game ends
    free_board(ctx);
    printf("Game Over!\n");
}