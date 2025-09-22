/*
This file will act like a manager of all the assets, it will run the functions from the other asset files that
are necessary for the game to run.
Example:
Random asset spawning
    * Spawn a random asset
Moving asset given an input
    * Move asset left, right, down, rotate
Collision detection
    * Check if asset collides with walls or other assets
    * Lock asset in place if it collides while falling
Line clearing
    * Check for and clear completed lines
    * Update score and level
This file wont do anything else for the game managment, that will be done in the main game loop in main.c
*/

#include "asset_manager.h"
#include "../render/render.h"
#include "../assets/cube.h"
#include "../assets/line.h"

#include <stdlib.h>
#include <time.h>

void random_asset() {
    // picks a random asset :)
    unsigned char asset_id = rand() % 6;
    switch (asset_id) {
        case 0:
            // spawn cube
            break;
        case 1:
            // spawn line
            break;
        case 2:
            // spawn L piece
            break;
        case 3:
            // spawn T piece
            break;
        case 4:
            // spawn S piece
            break;
        case 5:
            // spawn Z piece
            break;
        case 6:
            // spawn J piece
            break;
        default:
            printf("ERROR: Invalid asset ID\n");
            break;
    }
}

void spawn_asset(unsigned char asset_id) {
    switch (asset_id) {
        case 0:
            // spawn cube
            break;
        case 1:
            // spawn line
            break;
        case 2:
            // spawn L piece
            break;
        case 3:
            // spawn T piece
            break;
        case 4:
            // spawn S piece
            break;
        case 5:
            // spawn Z piece
            break;
        case 6:
            // spawn J piece
            break;
        default:
            printf("ERROR: Invalid asset ID\n");
            break;
    }
}

unsigned char manage_asset(unsigned char input, struct TetrisAsset* asset) {
    // manage asset movement and rotation based on input
    switch (input) {
        case 3: // Left Arrow
            asset->x--;
            break;
        case 4: // Right Arrow
            asset->x++;
            break;
        case 2: // Down Arrow
            asset->y++;
            break;
        case 1: // Up Arrow (rotate)
            // TODO: rotate asset
            break;
        default:
            // No action for other inputs
            break;
    }
    return 0; // return 0 for success, can be expanded for error handling
}

void check_collision(struct TetrisAsset* asset) {
    // check for collisions with walls or other assets
    // if collision detected, revert asset position or lock in place
}

void clear_lines() {
    // check for and clear completed lines
    // update score and level accordingly
}