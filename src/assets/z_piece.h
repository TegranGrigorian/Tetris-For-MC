#ifndef Z_PIECE_H
#define Z_PIECE_H

// this will be the asset for the Z-shaped piece

struct z_piece {
    int x; // x position of the Z piece
    int y; // y position of the Z piece
};

void draw_z_piece(struct z_piece* z);
void draw_z_piece_at_position(int x, int y);

#endif