#include "cube.h"

//function to draw a cube at its position
void draw_cube(struct cube* c) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("#");
        }
        printf("\n");
    }
}

//function to draw a cube at a specific position (for use with render context)
void draw_cube_at_position(int x, int y) {
    // This function can be used to check if a position should contain a cube block
    // The actual drawing is handled by the render context
}