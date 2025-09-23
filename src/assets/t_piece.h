#ifndef T_PIECE_H
#define T_PIECE_H

// this will be the asset for the T-shaped piece

struct t_piece {
    int x; // x position of the T piece
    int y; // y position of the T piece
};

void draw_t_piece(struct t_piece* t);
void draw_t_piece_at_position(int x, int y);

#endif