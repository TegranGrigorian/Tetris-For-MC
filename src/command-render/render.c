#include "render.h"
#include <unistd.h> // im slow

void render_frame(struct RenderContext* ctx) {
    // system("clear");  // Clear the terminal screen
    // printf("Rendering frame...\n");
    system("clear");  // Clear the terminal screen
    // print a * for the entire screen
    for (int y = 0; y < ctx->height; y++) {
        for (int x = 0; x < ctx->width; x++) {
            printf("*");
        }
        printf("\n");
    }
    // Render the game state using the context information
}

void water_fall(struct RenderContext* ctx) {
    system("clear");  // Clear the terminal screen
    // print a in the middle of the screen
    for (int y = 0; y < ctx->height; y++) {
        for (int x = 0; x < ctx->width; x++) {
            if (x == ctx->width / 2) {
                printf("a");
                sleep(1);
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
}