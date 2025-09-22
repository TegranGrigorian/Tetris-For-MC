#include "render.h"
#include <unistd.h> // im slow
#include "assets/cube.h"

// void render_frame(struct RenderContext* ctx) {
//     // system("clear");  // Clear the terminal screen
//     // printf("Rendering frame...\n");
//     system("clear");  // Clear the terminal screen
//     // print a * for the entire screen
//     for (int y = 0; y < ctx->height; y++) {
//         for (int x = 0; x < ctx->width; x++) {
//             printf("*");
//         }
//         printf("\n");
//     }
//     // Render the game state using the context information
// }

// void water_fall(struct RenderContext* ctx) {
//     system("clear");  // Clear the terminal screen
//     // print a in the middle of the screen
//     for (int y = 0; y < ctx->height; y++) {
//         for (int x = 0; x < ctx->width; x++) {
//             if (x == ctx->width / 2) {
//                 printf("a");
//                 sleep(1);
//             } else {
//                 printf("*");
//             }
//         }
//         printf("\n");
//     }
// }

// we need a 10 wide by 20 high grid, the grid will be empty, a block will the distingushed
// by a #, empty space is just empty space

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

void animate_falling_cube(struct RenderContext* ctx) {
    // Initialize cube position at the top center of the screen
    ctx->block_x = ctx->width / 2 - 1;  // Center the 2x2 cube
    ctx->block_y = 0;  // Start at the top
    
    // Animate the cube falling down
    while (ctx->block_y < ctx->height - 2) {  // Stop when cube reaches bottom
        render_frame(ctx);
        usleep(200000);  // Sleep for 200ms for smooth animation
        ctx->block_y++;  // Move cube down one row
    }
    
    // Render final frame when cube reaches bottom
    render_frame(ctx);
}