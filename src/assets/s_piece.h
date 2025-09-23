#ifndef S_PIECE_H
#define S_PIECE_H

// this will be the asset for the S-shaped piece

struct s_piece {
    int x; // x position of the S piece
    int y; // y position of the S piece
};

void draw_s_piece(struct s_piece* s);
void draw_s_piece_at_position(int x, int y);

#endif