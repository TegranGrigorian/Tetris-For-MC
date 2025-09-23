# File Structure
```
src/
├── assets
│   ├── cube.c
│   ├── cube.h
│   ├── j_piece.c
│   ├── j_piece.h
│   ├── line.c
│   ├── line.h
│   ├── l_piece.c
│   ├── l_piece.h
│   ├── readme.md
│   ├── s_piece.c
│   ├── s_piece.h
│   ├── t_piece.c
│   ├── t_piece.h
│   ├── z_piece.c
│   └── z_piece.h
├── game
│   ├── asset_manager.c
│   ├── asset_manager.h
│   ├── game_manager.c
│   ├── game_manager.h
│   └── readme.md
├── input
│   ├── input.c
│   └── input.h
├── main.c
├── readme.md
├── render
│   ├── render.c
│   └── render.h
└── test
    ├── test.c
    └── test.h
```

## Descirptions

### These are descriptions of folders

**assets**
* Contains initalization of asset object
---
**game**

* Contains managers that allow for the game to operate as well as asset manages allowing for the game pieces ot be manipulated
---
**input**
* Contains the code to take in user inputs from the keyboard and map them to specific keys then, this is passed to the game manager which takes the inputs and correlates them with game actions
---
**test**
* test scripts :)

___