#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

// Forward declarations
struct RenderContext;
struct TetrisAsset;

// Game management function declarations
void initialize_game(struct RenderContext* ctx);
void run_tetris_game(struct RenderContext* ctx, unsigned int refresh_rate);
void cleanup_game(struct RenderContext* ctx);

// Game state functions
int is_game_over(struct RenderContext* ctx, struct TetrisAsset* asset);
int clear_lines(struct RenderContext* ctx);
void update_score_and_level(struct RenderContext* ctx, int lines_cleared);

#endif // GAME_MANAGER_H
