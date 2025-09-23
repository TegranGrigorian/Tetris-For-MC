#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdlib.h>

// Enum for different Tetris asset types
typedef enum {
    ASSET_CUBE,
    ASSET_LINE,
    ASSET_L_PIECE,
    ASSET_T_PIECE,
    ASSET_S_PIECE,
    ASSET_Z_PIECE,
    ASSET_J_PIECE
} AssetType;

// Generic asset structure that can represent any Tetris piece
struct TetrisAsset {
    AssetType type;
    int width;          // Width of the asset
    int height;         // Height of the asset
    int x;              // Current x position
    int y;              // Current y position
    char** shape;       // 2D array representing the shape pattern
};

struct RenderContext {
    int width;
    int height;
    char* buffer;
    int block_x;  // x position of the falling block (legacy, will be replaced)
    int block_y;  // y position of the falling block (legacy, will be replaced)
    struct TetrisAsset* current_asset;  // Current falling asset
    char** board;  // 2D grid to track landed pieces (0 = empty, 1 = occupied)
    int score;     // Player's score
    int lines_cleared_total;  // Total lines cleared for speed calculation
    int level;     // Current level/speed
};

// Function declarations
void render_frame(struct RenderContext* ctx);
void render_frame_with_asset(struct RenderContext* ctx, struct TetrisAsset* asset);
void water_fall(struct RenderContext* ctx);
void animate_falling_cube(struct RenderContext* ctx, unsigned char refresh_rate);
void animate_falling_asset(struct RenderContext* ctx, struct TetrisAsset* asset, unsigned int refresh_rate);
void animate_interactive_falling_asset(struct RenderContext* ctx, struct TetrisAsset* asset, unsigned int refresh_rate);
void draw_asset(struct RenderContext* ctx, struct TetrisAsset* asset);
struct TetrisAsset* create_cube_asset(int x, int y);
struct TetrisAsset* create_line_asset(int x, int y);
struct TetrisAsset* create_l_piece_asset(int x, int y);
struct TetrisAsset* create_j_piece_asset(int x, int y);
struct TetrisAsset* create_t_piece_asset(int x, int y);
struct TetrisAsset* create_s_piece_asset(int x, int y);
struct TetrisAsset* create_z_piece_asset(int x, int y);
void free_asset(struct TetrisAsset* asset);
void init_board(struct RenderContext* ctx);
void free_board(struct RenderContext* ctx);
void lock_asset_to_board(struct RenderContext* ctx, struct TetrisAsset* asset);
void rotate_asset(struct TetrisAsset* asset);

#endif // RENDER_H