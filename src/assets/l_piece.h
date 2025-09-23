#ifndef L_PIECE_H
#define L_PIECE_H

// this will be the asset for the L-shaped piece

struct l_piece {
    int x; // x position of the L piece
    int y; // y position of the L piece
};

void draw_l_piece(struct l_piece* l);
void draw_l_piece_at_position(int x, int y);

#endif