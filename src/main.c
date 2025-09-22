#include <stdio.h>
#include <stdlib.h>
#include "command-render/render.h"

int main() {
    struct RenderContext ctx;
    ctx.width = 20;   // Narrower width for Tetris-like game
    ctx.height = 20;  // Square grid for Tetris
    ctx.buffer = (char*)malloc(ctx.width * ctx.height * 4);  // RGBA
    
    // Initialize block position (will be set by animate_falling_cube)
    ctx.block_x = 0;
    ctx.block_y = 0;

    printf("Starting Tetris cube animation...\n");
    printf("Press Ctrl+C to stop\n\n");
    
    // Run the falling cube animation
    animate_falling_cube(&ctx);
    
    printf("\nCube has reached the bottom!\n");
    
    free(ctx.buffer);
    return 0;
}