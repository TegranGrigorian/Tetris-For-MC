/*

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
*/

#ifndef LINE_H
#define LINE_H

// this will be the asset for the 1x4 line piece

struct line {
    int x; // x position of the line
    int y; // y position of the line
};

void draw_line(struct line* l);
void draw_line_at_position(int x, int y);

#endif