#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "command-render/render.h"
#include "input-manager/input.h"
#include "test.h"

void cube_fall_test() {
    struct RenderContext ctx;
    ctx.width = 20;
    ctx.height = 20;
    ctx.buffer = malloc(ctx.width * ctx.height);
    
    printf("Demonstrating falling cube...\n");
    struct TetrisAsset* cube = create_cube_asset(0, 0);
    animate_falling_asset(&ctx, cube, 300);  // 300ms refresh rate
    printf("Cube animation complete!\n");
    
    free_asset(cube);
    free(ctx.buffer);
}

void line_fall_test() {
    struct RenderContext ctx;
    ctx.width = 20;
    ctx.height = 20;
    ctx.buffer = malloc(ctx.width * ctx.height);

    printf("Demonstrating falling line...\n");
    struct TetrisAsset* line = create_line_asset(0, 0);
    animate_falling_asset(&ctx, line, 150);  // 150ms refresh rate (faster)
    printf("Line animation complete!\n");

    free_asset(line);
    free(ctx.buffer);
}

void input_test() {
    printf("Testing input system. Press arrow keys or 'q' to quit.\n");
    printf("Arrow keys should return: 1=Up, 2=Down, 3=Left, 4=Right\n\n");
    
    do {
        char input = get_input();
        if (input == 'Q' || input == 'q') {
            printf("\nQuitting...\n");
            break;
        } else if (input != 0) {
            printf("Input: %c (ID: %d)\n", input, input);
        }
        usleep(100000); // Small delay to prevent spam
    } while (1);
}