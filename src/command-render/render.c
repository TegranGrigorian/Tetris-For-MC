#include "render.h"
#include <unistd.h> // im slow
#include "assets/cube.h"
#include "assets/line.h"

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

// Render frame with a specific asset
void render_frame_with_asset(struct RenderContext* ctx, struct TetrisAsset* asset) {
    system("clear");  // Clear the terminal screen
    for (int y = 0; y < ctx->height; y++) {
        for (int x = 0; x < ctx->width; x++) {
            char pixel = ' ';  // Default to empty space
            
            // Check if this position is part of the asset
            if (asset && 
                x >= asset->x && x < asset->x + asset->width &&
                y >= asset->y && y < asset->y + asset->height) {
                int asset_x = x - asset->x;
                int asset_y = y - asset->y;
                pixel = asset->shape[asset_y][asset_x];
            }
            
            printf("%c", pixel);
        }
        printf("\n");
    }
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