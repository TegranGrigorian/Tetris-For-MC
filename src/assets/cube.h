//this code is for the cube object, a 2x2 matrix of #

#ifndef CUBE_H
#define CUBE_H
#include <stdio.h>

struct cube {
    int x; // x position of the cube
    int y; // y position of the cube
};

// Function declarations
void draw_cube(struct cube* c);
void draw_cube_at_position(int x, int y);
#endif