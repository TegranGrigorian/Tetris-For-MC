/*
Asset Manager - Handles asset-specific operations only
This file manages:
- Asset spawning and creation
- Asset movement and rotation
- Collision detection between assets and board
- Asset landing detection
- Asset-to-board interaction

Game logic, scoring, and flow control are handled by game_manager.c
*/

#include "asset_manager.h"
#include "../render/render.h"
#include "../input/input.h"
#include "../assets/cube.h"
#include "../assets/line.h"
#include "../assets/l_piece.h"
#include "../assets/j_piece.h"
#include "../assets/t_piece.h"
#include "../assets/s_piece.h"
#include "../assets/z_piece.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

// Check if asset has landed (hit bottom or another asset)
int has_asset_landed(struct TetrisAsset* asset, struct RenderContext* ctx) {
    // Check if asset hit the bottom
    if (asset->y + asset->height >= ctx->height) {
        return 1;
    }
    
    // Check collision with landed pieces on the board
    for (int y = 0; y < asset->height; y++) {
        for (int x = 0; x < asset->width; x++) {
            if (asset->shape[y][x] == '@') {
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
}
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
            new_asset = create_l_piece_asset(spawn_x - 1, spawn_y); // L piece (2x3)
            break;
        case 3: // spawn T piece
            new_asset = create_t_piece_asset(spawn_x - 1, spawn_y); // T piece (3x2)
            break;
        case 4: // spawn S piece
            new_asset = create_s_piece_asset(spawn_x - 1, spawn_y); // S piece (3x2)
            break;
        case 5: // spawn Z piece
            new_asset = create_z_piece_asset(spawn_x - 1, spawn_y); // Z piece (3x2)
            break;
        case 6: // spawn J piece
            new_asset = create_j_piece_asset(spawn_x - 1, spawn_y); // J piece (2x3)
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
    
    // Now we have all 7 Tetris pieces: cube=0, line=1, L=2, T=3, S=4, Z=5, J=6
    return rand() % 7;  // All 7 pieces available
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
            // Check if piece has already landed - if so, hard drop (instant lock)
            if (has_asset_landed(asset, ctx)) {
                return 1; // Signal for hard drop/instant lock
            }
            
            // Otherwise, try to move down normally
            if (asset->y + asset->height < ctx->height) {  // Check bottom boundary first
                int old_y = asset->y;
                asset->y++;
                
                // Check for collision with landed pieces or if would land
                if (check_asset_collision(asset, ctx) || has_asset_landed(asset, ctx)) {
                    asset->y = old_y;  // Revert movement if collision or would land
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
            if (asset->shape[y][x] == '@') {
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