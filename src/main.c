#include <stdio.h>
#include <stdlib.h>
#include "command-render/render.h"
int main() {
    struct RenderContext ctx;
    ctx.width = 80;  // More reasonable for terminal
    ctx.height = 24; // Standard terminal height
    ctx.buffer = (char*)malloc(ctx.width * ctx.height * 4);  // RGBA

    render_frame(&ctx);
    water_fall(&ctx);
    free(ctx.buffer);
    return 0;
}