#include <unistd.h>
#include "test.h"

int main() {
    // struct RenderContext ctx;
    // ctx.width = 20;   // Narrower width for Tetris-like game
    // ctx.height = 20;  // Square grid for Tetris
    // ctx.buffer = (char*)malloc(ctx.width * ctx.height * 4);  // RGBA
    
    // // Initialize block position (legacy)
    // ctx.block_x = 0;
    // ctx.block_y = 0;
    // ctx.current_asset = NULL;

    // printf("Starting Tetris asset animation demo...\n");
    // printf("Press Ctrl+C to stop\n\n");
    
    // // Test cube animation
    // printf("Demonstrating falling cube...\n");
    // struct TetrisAsset* cube = create_cube_asset(0, 0);
    // animate_falling_asset(&ctx, cube, 200);  // 200ms refresh rate
    // printf("Cube animation complete!\n\n");
    
    // // Wait a moment
    // usleep(1000000);  // 1 second pause
    
    // Test line animation
    // printf("Demonstrating falling line...\n");
    // struct TetrisAsset* line = create_line_asset(0, 0);
    // animate_falling_asset(&ctx, line, 150);  // 150ms refresh rate (faster)
    // printf("Line animation complete!\n");
    
    // // Clean up
    // // free_asset(cube);
    // free_asset(line);
    // free(ctx.buffer);

    // --- Tests ---
    // cube_fall_test();
    // usleep(1000000);
    // line_fall_test();
    input_test();
    return 0;
}