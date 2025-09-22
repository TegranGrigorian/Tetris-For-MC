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