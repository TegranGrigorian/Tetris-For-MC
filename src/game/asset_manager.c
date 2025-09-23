

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

int has_asset_landed(struct TetrisAsset* asset, struct RenderContext* ctx) {
    if (asset->y + asset->height >= ctx->height) {
        return 1;
    }
    
    for (int y = 0; y < asset->height; y++) {
        for (int x = 0; x < asset->width; x++) {
            if (asset->shape[y][x] == '@') {
                int board_x = asset->x + x;
                int board_y = asset->y + y + 1;
                
                if (board_x >= 0 && board_x < ctx->width && 
                    board_y >= 0 && board_y < ctx->height) {
                    if (ctx->board[board_y][board_x] == 1) {
                        return 1;
                    }
                }
            }
        }
    }
    
    return 0;
}
struct TetrisAsset* spawn_asset(unsigned char asset_id, struct RenderContext* ctx) {
    struct TetrisAsset* new_asset = NULL;
    int spawn_x = ctx->width / 2;
    int spawn_y = 0;
    
    switch (asset_id) {
        case 0:
            new_asset = create_cube_asset(spawn_x - 1, spawn_y);
            break;
        case 1:
            new_asset = create_line_asset(spawn_x, spawn_y);
            break;
        case 2:
            new_asset = create_l_piece_asset(spawn_x - 1, spawn_y);
            break;
        case 3:
            new_asset = create_t_piece_asset(spawn_x - 1, spawn_y);
            break;
        case 4:
            new_asset = create_s_piece_asset(spawn_x - 1, spawn_y);
            break;
        case 5:
            new_asset = create_z_piece_asset(spawn_x - 1, spawn_y);
            break;
        case 6:
            new_asset = create_j_piece_asset(spawn_x - 1, spawn_y);
            break;
        default:
            printf("ERROR: Invalid asset ID %d\n", asset_id);
            new_asset = create_cube_asset(spawn_x - 1, spawn_y);
            break;
    }
    
    return new_asset;
}

unsigned char random_asset() {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    
    return rand() % 7;
}

unsigned char manage_asset(unsigned char input, struct TetrisAsset* asset, struct RenderContext* ctx) {
    switch (input) {
        case 3:
            if (asset->x > 0) {
                int old_x = asset->x;
                asset->x--;
                
                if (check_asset_collision(asset, ctx)) {
                    asset->x = old_x;
                }
            }
            break;
        case 4:
            if (asset->x + asset->width < ctx->width) {
                int old_x = asset->x;
                asset->x++;
                
                if (check_asset_collision(asset, ctx)) {
                    asset->x = old_x;
                }
            }
            break;
        case 2:
            if (has_asset_landed(asset, ctx)) {
                return 1;
            }
            
            if (asset->y + asset->height < ctx->height) {
                int old_y = asset->y;
                asset->y++;
                
                if (check_asset_collision(asset, ctx) || has_asset_landed(asset, ctx)) {
                    asset->y = old_y;
                }
            }
            break;
        case 1:
            {
                int old_width = asset->width;
                int old_height = asset->height;
                char** old_shape = asset->shape;
                
                char** backup_shape = malloc(old_height * sizeof(char*));
                for (int i = 0; i < old_height; i++) {
                    backup_shape[i] = malloc((old_width + 1) * sizeof(char));
                    strcpy(backup_shape[i], old_shape[i]);
                }
                
                rotate_asset(asset);
                
                if (asset->x + asset->width > ctx->width || 
                    asset->y + asset->height > ctx->height ||
                    check_asset_collision(asset, ctx)) {
                    
                    for (int i = 0; i < asset->height; i++) {
                        free(asset->shape[i]);
                    }
                    free(asset->shape);
                    
                    asset->shape = backup_shape;
                    asset->width = old_width;
                    asset->height = old_height;
                } else {
                    for (int i = 0; i < old_height; i++) {
                        free(backup_shape[i]);
                    }
                    free(backup_shape);
                }
            }
            break;
        default:
            break;
    }
    return 0;
}

void check_collision(struct TetrisAsset* asset) {
}

int check_asset_collision(struct TetrisAsset* asset, struct RenderContext* ctx) {
    for (int y = 0; y < asset->height; y++) {
        for (int x = 0; x < asset->width; x++) {
            if (asset->shape[y][x] == '@') {
                int board_x = asset->x + x;
                int board_y = asset->y + y;
                
                if (board_x >= 0 && board_x < ctx->width && 
                    board_y >= 0 && board_y < ctx->height) {
                    if (ctx->board[board_y][board_x] == 1) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}