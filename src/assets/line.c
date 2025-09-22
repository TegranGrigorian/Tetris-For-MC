#include <stdio.h>
#include "line.h"

void draw_line(struct line *l) { //given input of a line struct, draw a 1x4 line at its position
    for (int i = 0; i < 4; i++) {
        printf("#");
    }
    printf("\n");
}
void draw_line_at_position(int x, int y) {
    // This function can be used to check if a position should contain a line block
    // The actual drawing is handled by the render context
}