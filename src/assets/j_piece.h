#ifndef J_PIECE_H
#define J_PIECE_H

// this will be the asset for the J-shaped piece

struct j_piece {
    int x; // x position of the J piece
    int y; // y position of the J piece
};

void draw_j_piece(struct j_piece* j);
void draw_j_piece_at_position(int x, int y);

#endif