#include <stdio.h>
#include "j_piece.h"

void draw_j_piece(struct j_piece *j) {
    // Draw the J piece pattern
    printf(" #\n");
    printf(" #\n");
    printf("##\n");
}

void draw_j_piece_at_position(int x, int y) {
    // This function can be used to check if a position should contain a J piece block
    // The actual drawing is handled by the render context
}