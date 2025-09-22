Organized file tree:

```
src/
├── main.c                    # Main game loop
├── game/                     # Game logic & state management
│   ├── asset_manager.c       # Your current asset.c (renamed)
│   ├── asset_manager.h
│   ├── collision.c           # Collision detection
│   ├── collision.h
│   ├── game_state.c          # Game state (score, level, etc.)
│   └── game_state.h
├── assets/                   # Individual Tetris piece definitions
│   ├── cube.c
│   ├── cube.h
│   ├── line.c
│   ├── line.h
│   ├── t_piece.c             # Future pieces
│   └── piece_common.h        # Common piece structures
├── render/                   # Rendering system
│   ├── render.c
│   ├── render.h
│   └── display.c             # Screen management
├── input/                    # Input handling
│   ├── input.c
│   └── input.h
└── test/                     # Testing utilities
    ├── test.c
    └── test.h
```