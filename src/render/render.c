#include "render.h"
#include <unistd.h>
#include <string.h>
#include "../assets/cube.h"
#include "../assets/line.h"
#include "../assets/l_piece.h"
#include "../assets/j_piece.h"
#include "../assets/t_piece.h"
#include "../assets/s_piece.h"
#include "../assets/z_piece.h"
#include "../input/input.h"
#include "../game/asset_manager.h"

void render_frame(struct RenderContext* ctx) {
    system("clear");
    for (int y = 0; y < ctx->height; y++) {
        for (int x = 0; x < ctx->width; x++) {
            if (x >= ctx->block_x && x < ctx->block_x + 2 && y >= ctx->block_y && y < ctx->block_y + 2) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void animate_falling_cube(struct RenderContext* ctx, unsigned char refresh_rate) {
    ctx->block_x = ctx->width / 2 - 1;
    ctx->block_y = 0;
    
    while (ctx->block_y < ctx->height - 2) {
        render_frame(ctx);
        usleep(refresh_rate * 1000);
        ctx->block_y++;
    }
    
    render_frame(ctx);
}

struct TetrisAsset* create_cube_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_CUBE;
    asset->width = 2;
    asset->height = 2;
    asset->x = x;
    asset->y = y;
    
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc(asset->width * sizeof(char));
        for (int j = 0; j < asset->width; j++) {
            asset->shape[i][j] = '@';
        }
    }
    
    return asset;
}

struct TetrisAsset* create_line_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_LINE;
    asset->width = 1;
    asset->height = 4;
    asset->x = x;
    asset->y = y;
    
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc(asset->width * sizeof(char));
        asset->shape[i][0] = '@';
    }
    
    return asset;
}

void free_asset(struct TetrisAsset* asset) {
    if (asset) {
        for (int i = 0; i < asset->height; i++) {
            free(asset->shape[i]);
        }
        free(asset->shape);
        free(asset);
    }
}

void draw_asset(struct RenderContext* ctx, struct TetrisAsset* asset) {
}

void render_frame_with_asset(struct RenderContext* ctx, struct TetrisAsset* asset) {
    printf("\033[H\033[J");
    
    printf("┌────────────────────────────────────────┐\n");
    printf("│ Score: %-8d Level: %-2d Lines: %-3d │\n", 
           ctx->score, ctx->level, ctx->lines_cleared_total);
    printf("└────────────────────────────────────────┘\n");
    
    printf("┌");
    for (int i = 0; i < ctx->width; i++) {
        printf("─");
    }
    printf("┐\n");
    
    for (int y = 0; y < ctx->height; y++) {
        printf("│");
        for (int x = 0; x < ctx->width; x++) {
            char pixel = ' ';
            
            if (ctx->board && ctx->board[y][x] == 1) {
                pixel = '@';
            }
            
            if (asset && 
                x >= asset->x && x < asset->x + asset->width &&
                y >= asset->y && y < asset->y + asset->height) {
                int asset_x = x - asset->x;
                int asset_y = y - asset->y;
                if (asset->shape[asset_y][asset_x] == '@') {
                    pixel = '@';
                }
            }
            
            printf("%c", pixel);
        }
        printf("│\n");
    }
    
    printf("└");
    for (int i = 0; i < ctx->width; i++) {
        printf("─");
    }
    printf("┘\n");
}

void animate_falling_asset(struct RenderContext* ctx, struct TetrisAsset* asset, unsigned int refresh_rate) {
    if (!asset) return;
    
    asset->x = ctx->width / 2 - asset->width / 2;
    asset->y = 0;
    
    while (asset->y < ctx->height - asset->height) {
        render_frame_with_asset(ctx, asset);
        usleep(refresh_rate * 1000);
        asset->y++;
    }
    
    render_frame_with_asset(ctx, asset);
}

// Interactive falling asset - player can control movement
// Interactive falling asset - player can control movement
void animate_interactive_falling_asset(struct RenderContext* ctx, struct TetrisAsset* asset, unsigned int refresh_rate) {/* Lines 155-192 omitted */}

void init_board(struct RenderContext* ctx) {
    ctx->board = malloc(ctx->height * sizeof(char*));
    for (int y = 0; y < ctx->height; y++) {
        ctx->board[y] = calloc(ctx->width, sizeof(char));
    }
}

void free_board(struct RenderContext* ctx) {
    if (ctx->board) {
        for (int y = 0; y < ctx->height; y++) {
            free(ctx->board[y]);
        }
        free(ctx->board);
        ctx->board = NULL;
    }
}

void lock_asset_to_board(struct RenderContext* ctx, struct TetrisAsset* asset) {
    for (int y = 0; y < asset->height; y++) {
        for (int x = 0; x < asset->width; x++) {
            if (asset->shape[y][x] == '@') {
                int board_x = asset->x + x;
                int board_y = asset->y + y;
                
                if (board_x >= 0 && board_x < ctx->width && 
                    board_y >= 0 && board_y < ctx->height) {
                    ctx->board[board_y][board_x] = 1;
                }
            }
        }
    }
}

void rotate_asset(struct TetrisAsset* asset) {
    if (asset->type == ASSET_CUBE) {
        return;
    }
    
    int new_width = asset->height;
    int new_height = asset->width;
    
    char** new_shape = malloc(new_height * sizeof(char*));
    for (int i = 0; i < new_height; i++) {
        new_shape[i] = malloc((new_width + 1) * sizeof(char));
        new_shape[i][new_width] = '\0';
    }
    
    for (int i = 0; i < asset->height; i++) {
        for (int j = 0; j < asset->width; j++) {
            new_shape[j][asset->height - 1 - i] = asset->shape[i][j];
        }
    }
    
    for (int i = 0; i < asset->height; i++) {
        free(asset->shape[i]);
    }
    free(asset->shape);
    
    asset->shape = new_shape;
    asset->width = new_width;
    asset->height = new_height;
}

struct TetrisAsset* create_l_piece_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_L_PIECE;
    asset->width = 2;
    asset->height = 3;
    asset->x = x;
    asset->y = y;
    
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc((asset->width + 1) * sizeof(char));
        asset->shape[i][asset->width] = '\0';
    }
    
    strcpy(asset->shape[0], "@ ");
    strcpy(asset->shape[1], "@ ");
    strcpy(asset->shape[2], "@@");
    
    return asset;
}

// Create a J piece asset
struct TetrisAsset* create_j_piece_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_J_PIECE;
    asset->width = 2;
    asset->height = 3;
    asset->x = x;
    asset->y = y;
    
    // Allocate memory for the shape pattern
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc((asset->width + 1) * sizeof(char));
        asset->shape[i][asset->width] = '\0';
    }
    
    // Define J piece shape
    strcpy(asset->shape[0], " @");
    strcpy(asset->shape[1], " @");
    strcpy(asset->shape[2], "@@");
    
    return asset;
}

// Create a T piece asset
struct TetrisAsset* create_t_piece_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_T_PIECE;
    asset->width = 3;
    asset->height = 2;
    asset->x = x;
    asset->y = y;
    
    // Allocate memory for the shape pattern
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc((asset->width + 1) * sizeof(char));
        asset->shape[i][asset->width] = '\0';
    }
    
    // Define T piece shape
    strcpy(asset->shape[0], "@@@");
    strcpy(asset->shape[1], " @ ");
    
    return asset;
}

// Create an S piece asset
struct TetrisAsset* create_s_piece_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_S_PIECE;
    asset->width = 3;
    asset->height = 2;
    asset->x = x;
    asset->y = y;
    
    // Allocate memory for the shape pattern
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc((asset->width + 1) * sizeof(char));
        asset->shape[i][asset->width] = '\0';
    }
    
    // Define S piece shape
    strcpy(asset->shape[0], " @@");
    strcpy(asset->shape[1], "@@ ");
    
    return asset;
}

// Create a Z piece asset
struct TetrisAsset* create_z_piece_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_Z_PIECE;
    asset->width = 3;
    asset->height = 2;
    asset->x = x;
    asset->y = y;
    
    // Allocate memory for the shape pattern
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc((asset->width + 1) * sizeof(char));
        asset->shape[i][asset->width] = '\0';
    }
    
    // Define Z piece shape
    strcpy(asset->shape[0], "@@ ");
    strcpy(asset->shape[1], " @@");
    
    return asset;
}