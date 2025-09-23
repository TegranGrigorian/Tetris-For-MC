#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../render/render.h"
#include "../input/input.h"
#include "../game/asset_manager.h"
#include "../game/game_manager.h"
#include "test.h"

void cube_fall_test() {
    struct RenderContext ctx;
    ctx.width = 20;
    ctx.height = 20;
    ctx.buffer = malloc(ctx.width * ctx.height);
    init_board(&ctx);  // Initialize the board
    
    printf("Demonstrating falling cube...\n");
    struct TetrisAsset* cube = create_cube_asset(0, 0);
    animate_falling_asset(&ctx, cube, 300);  // 300ms refresh rate
    printf("Cube animation complete!\n");
    
    free_asset(cube);
    free_board(&ctx);  // Clean up the board
    free(ctx.buffer);
}

void line_fall_test() {
    struct RenderContext ctx;
    ctx.width = 20;
    ctx.height = 20;
    ctx.buffer = malloc(ctx.width * ctx.height);
    init_board(&ctx);  // Initialize the board

    printf("Demonstrating falling line...\n");
    struct TetrisAsset* line = create_line_asset(0, 0);
    animate_falling_asset(&ctx, line, 150);  // 150ms refresh rate (faster)
    printf("Line animation complete!\n");

    free_asset(line);
    free_board(&ctx);  // Clean up the board
    free(ctx.buffer);
}

void input_test() {
    printf("Testing input system. Press arrow keys or 'q' to quit.\n");
    printf("Arrow keys should return: 1=Up, 2=Down, 3=Left, 4=Right\n\n");
    
    do {
        char input = get_input();
        if (input == 'Q' || input == 'q') {
            printf("\nQuitting...\n");
            break;
        } else if (input != 0) {
            printf("Input: %c (ID: %d)\n", input, input);
        }
        usleep(100000); // Small delay to prevent spam
    } while (1);
}

void interactive_asset_test() {
    struct RenderContext ctx;
    ctx.width = 20;
    ctx.height = 20;
    ctx.buffer = malloc(ctx.width * ctx.height);
    init_board(&ctx);  // Initialize the board
    
    printf("Tetris Test!\n");
    printf("┌─────────────────────────────────┐\n");
    printf("│          CONTROLS               │\n");
    printf("│  ←  →  : Move left/right        │\n");
    printf("│  ↓     : Move down faster       │\n");
    printf("│  ↑     : Rotate piece           │\n");
    printf("│  q     : Quit game              │\n");
    printf("└─────────────────────────────────┘\n");
    printf("\nFeatures:\n");
    printf("  • Visible boundaries\n");
    printf("  • Piece rotation\n");
    printf("  • Smooth one-input-per-frame control\n");
    printf("  • Automatic falling\n\n");
    printf("Press any key to start...\n");
    get_single_input(); // Wait for user to be ready
    
    struct TetrisAsset* cube = create_cube_asset(0, 0);
    animate_interactive_falling_asset(&ctx, cube, 80);  // 80ms refresh rate for responsive control
    
    free_asset(cube);
    free_board(&ctx);  // Clean up the board
    free(ctx.buffer);
}

void continuous_spawn_test() {
    struct RenderContext ctx;
    ctx.width = 20;
    ctx.height = 20;
    ctx.buffer = malloc(ctx.width * ctx.height);
    
    printf("🎮 Complete Tetris Game!\n");
    printf("┌─────────────────────────────────┐\n");
    printf("│        FULL TETRIS GAME         │\n");
    printf("│  ←  →  : Move left/right        │\n");
    printf("│  ↓     : Move down faster       │\n");
    printf("│  ↑     : Rotate piece           │\n");
    printf("│  q     : Quit game              │\n");
    printf("└─────────────────────────────────┘\n");
    printf("\n✨ Features:\n");
    printf("  • All 7 Tetris pieces (I,O,T,S,Z,J,L)\n");
    printf("  • Piece rotation with ↑ key\n");
    printf("  • Line clearing & scoring\n");
    printf("  • Progressive speed increase\n");
    printf("  • Game over detection\n");
    printf("  • Smooth responsive controls\n");
    printf("  • Polished UI & scoring display\n\n");
    printf("Press any key to start the complete Tetris experience...\n");
    get_single_input(); // Wait for user to be ready
    
    // Run the continuous Tetris game with even faster refresh rate for smoother movement
    run_tetris_game(&ctx, 30);  // 30ms refresh rate for very responsive controls
    
    free(ctx.buffer);
}