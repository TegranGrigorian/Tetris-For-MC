#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdlib.h>

struct RenderContext {
    int width;
    int height;
    char* buffer;
    int block_x;  // x position of the falling block
    int block_y;  // y position of the falling block
};

void render_frame(struct RenderContext* ctx);
void water_fall(struct RenderContext* ctx);
void animate_falling_cube(struct RenderContext* ctx);
#endif // RENDER_H