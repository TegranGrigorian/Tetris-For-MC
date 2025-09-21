#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <stdlib.h>

struct RenderContext {
    int width;
    int height;
    char* buffer;
};

void render_frame(struct RenderContext* ctx);
void water_fall(struct RenderContext* ctx);
#endif // RENDER_H