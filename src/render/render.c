#include "render.h"
#include <unistd.h> // im slow
#include "../assets/cube.h"
#include "../assets/line.h"
#include "../input/input.h"
#include "../game/asset_manager.h"

void render_frame(struct RenderContext* ctx) {
    system("clear");  // Clear the terminal screen
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
    // Initialize cube position at the top center of the screen
    ctx->block_x = ctx->width / 2 - 1;  // Center the 2x2 cube
    ctx->block_y = 0;  // Start at the top
    
    // Animate the cube falling down
    while (ctx->block_y < ctx->height - 2) {  // Stop when cube reaches bottom
        render_frame(ctx);
        usleep(refresh_rate * 1000);  // Sleep for refresh_rate milliseconds for smooth animation
        ctx->block_y++;  // Move cube down one row
    }
    
    // Render final frame when cube reaches bottom
    render_frame(ctx);
}

// Create a cube asset
struct TetrisAsset* create_cube_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_CUBE;
    asset->width = 2;
    asset->height = 2;
    asset->x = x;
    asset->y = y;
    
    // Allocate memory for the shape pattern
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc(asset->width * sizeof(char));
        for (int j = 0; j < asset->width; j++) {
            asset->shape[i][j] = '#';  // Fill with '#' for cube
        }
    }
    
    return asset;
}

// Create a line asset (vertical by default)
struct TetrisAsset* create_line_asset(int x, int y) {
    struct TetrisAsset* asset = malloc(sizeof(struct TetrisAsset));
    asset->type = ASSET_LINE;
    asset->width = 1;
    asset->height = 4;
    asset->x = x;
    asset->y = y;
    
    // Allocate memory for the shape pattern
    asset->shape = malloc(asset->height * sizeof(char*));
    for (int i = 0; i < asset->height; i++) {
        asset->shape[i] = malloc(asset->width * sizeof(char));
        asset->shape[i][0] = '#';  // Vertical line
    }
    
    return asset;
}

// Free an asset's memory
void free_asset(struct TetrisAsset* asset) {
    if (asset) {
        for (int i = 0; i < asset->height; i++) {
            free(asset->shape[i]);
        }
        free(asset->shape);
        free(asset);
    }
}

// Generic function to draw any asset
void draw_asset(struct RenderContext* ctx, struct TetrisAsset* asset) {
    // This function checks if a given position should contain part of the asset
    // The actual rendering is handled by render_frame_with_asset
}

// Render frame with a specific asset and boundaries
void render_frame_with_asset(struct RenderContext* ctx, struct TetrisAsset* asset) {
    // Use more efficient clear - just move cursor to top
    printf("\033[H\033[J");  // Move cursor to home and clear screen (less flickering)
    
    // Display score and level at the top
    printf("Score: %d  Level: %d  Lines: %d\n", ctx->score, ctx->level, ctx->lines_cleared_total);
    
    // Draw top border
    printf("┌");
    for (int i = 0; i < ctx->width; i++) {
        printf("─");
    }
    printf("┐\n");
    
    // Draw game area with side walls
    for (int y = 0; y < ctx->height; y++) {
        printf("│");  // Left wall
        for (int x = 0; x < ctx->width; x++) {
            char pixel = ' ';  // Default to empty space
            
            // First check if this position has a landed piece on the board
            if (ctx->board && ctx->board[y][x] == 1) {
                pixel = '#';  // Landed piece
            }
            
            // Then check if this position is part of the current falling asset
            if (asset && 
                x >= asset->x && x < asset->x + asset->width &&
                y >= asset->y && y < asset->y + asset->height) {
                int asset_x = x - asset->x;
                int asset_y = y - asset->y;
                if (asset->shape[asset_y][asset_x] == '#') {
                    pixel = '#';  // Current falling asset
                }
            }
            
            printf("%c", pixel);
        }
        printf("│\n");  // Right wall
    }
    
    // Draw bottom border
    printf("└");
    for (int i = 0; i < ctx->width; i++) {
        printf("─");
    }
    printf("┘\n");
}

// Generic function to animate any falling asset
void animate_falling_asset(struct RenderContext* ctx, struct TetrisAsset* asset, unsigned int refresh_rate) {
    if (!asset) return;
    
    // Initialize asset position at the top center of the screen
    asset->x = ctx->width / 2 - asset->width / 2;  // Center the asset
    asset->y = 0;  // Start at the top
    
    // Animate the asset falling down
    while (asset->y < ctx->height - asset->height) {  // Stop when asset reaches bottom
        render_frame_with_asset(ctx, asset);
        usleep(refresh_rate * 1000);  // Sleep for refresh_rate milliseconds
        asset->y++;  // Move asset down one row
    }
    
    // Render final frame when asset reaches bottom
    render_frame_with_asset(ctx, asset);
}

// Interactive falling asset - player can control movement
// Interactive falling asset - player can control movement
void animate_interactive_falling_asset(struct RenderContext* ctx, struct TetrisAsset* asset, unsigned int refresh_rate) {/* Lines 155-192 omitted */}

// Initialize the board grid
void init_board(struct RenderContext* ctx) {
    ctx->board = malloc(ctx->height * sizeof(char*));
    for (int y = 0; y < ctx->height; y++) {
        ctx->board[y] = calloc(ctx->width, sizeof(char));
    }
}

// Free the board memory
void free_board(struct RenderContext* ctx) {
    if (ctx->board) {
        for (int y = 0; y < ctx->height; y++) {
            free(ctx->board[y]);
        }
        free(ctx->board);
        ctx->board = NULL;
    }
}

// Lock an asset to the board when it lands
void lock_asset_to_board(struct RenderContext* ctx, struct TetrisAsset* asset) {
    for (int y = 0; y < asset->height; y++) {
        for (int x = 0; x < asset->width; x++) {
            if (asset->shape[y][x] == '#') {
                int board_x = asset->x + x;
                int board_y = asset->y + y;
                
                // Make sure we're within bounds
                if (board_x >= 0 && board_x < ctx->width && 
                    board_y >= 0 && board_y < ctx->height) {
                    ctx->board[board_y][board_x] = 1;
                }
            }
        }
    }
}

// Rotate an asset 90 degrees clockwise
void rotate_asset(struct TetrisAsset* asset) {
    // Don't rotate cubes (they look the same rotated)
    if (asset->type == ASSET_CUBE) {
        return;
    }
    
    // Create temporary storage for the rotated shape
    int new_width = asset->height;
    int new_height = asset->width;
    
    // Allocate memory for rotated shape
    char** new_shape = malloc(new_height * sizeof(char*));
    for (int i = 0; i < new_height; i++) {
        new_shape[i] = malloc((new_width + 1) * sizeof(char));
        new_shape[i][new_width] = '\0';  // Null terminate
    }
    
    // Perform 90-degree clockwise rotation
    // Formula: new[j][height-1-i] = original[i][j]
    for (int i = 0; i < asset->height; i++) {
        for (int j = 0; j < asset->width; j++) {
            new_shape[j][asset->height - 1 - i] = asset->shape[i][j];
        }
    }
    
    // Free old shape
    for (int i = 0; i < asset->height; i++) {
        free(asset->shape[i]);
    }
    free(asset->shape);
    
    // Update asset with rotated shape
    asset->shape = new_shape;
    asset->width = new_width;
    asset->height = new_height;
}