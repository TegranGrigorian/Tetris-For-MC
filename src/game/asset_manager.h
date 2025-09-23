#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

// Forward declarations
struct TetrisAsset;
struct RenderContext;

// Function declarations
unsigned char random_asset();
struct TetrisAsset* spawn_asset(unsigned char asset_id, struct RenderContext* ctx);
unsigned char manage_asset(unsigned char input, struct TetrisAsset* asset, struct RenderContext* ctx);
void check_collision(struct TetrisAsset* asset);
int check_asset_collision(struct TetrisAsset* asset, struct RenderContext* ctx);
int has_asset_landed(struct TetrisAsset* asset, struct RenderContext* ctx);
int clear_lines(struct RenderContext* ctx);
void run_tetris_game(struct RenderContext* ctx, unsigned int refresh_rate);

#endif //ASSET_MANAGER_H