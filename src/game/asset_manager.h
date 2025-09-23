#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

// Forward declarations
struct TetrisAsset;
struct RenderContext;

// Asset management function declarations
unsigned char random_asset();
struct TetrisAsset* spawn_asset(unsigned char asset_id, struct RenderContext* ctx);
unsigned char manage_asset(unsigned char input, struct TetrisAsset* asset, struct RenderContext* ctx);

// Asset collision and state functions
void check_collision(struct TetrisAsset* asset);
int check_asset_collision(struct TetrisAsset* asset, struct RenderContext* ctx);
int has_asset_landed(struct TetrisAsset* asset, struct RenderContext* ctx);

#endif //ASSET_MANAGER_H