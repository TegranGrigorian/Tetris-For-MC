# Description
This is a Tetris game running inside of a terminal. It tkaes in user inputs from a keyboard to operate the game. This will eventually be used in a microcontroller, mapping inputs to microcontroller ports and output to a lcd screen. The purpose of this was to create the game logic prior to the construction of the microcontroller circuit.

# Organized file tree:

```
Tetris-For-MC/
├── Makefile
├── README.md
└── src
    ├── main.c
    ├── assets
    │   ├── cube.c
    │   ├── cube.h
    │   ├── line.c
    │   └── line.h
    ├── game
    │   ├── asset_manager.c
    │   └── asset_manager.h
    ├── input
    │   ├── input.c
    │   └── input.h
    ├── render
    │   ├── render.c
    │   └── render.h
    └── test
        ├── test.c
        └── test.h
```

# Notes
Yes this is all in C and yes this isnt the best idc