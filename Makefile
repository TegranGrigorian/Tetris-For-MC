# Updated Makefile for new directory structure with game_manager.c
# src/render/render.h
# src/main.c

#compile the program
all: src/main.o src/render/render.o src/test/test.o src/input/input.o src/assets/cube.o src/assets/line.o src/assets/l_piece.o src/assets/j_piece.o src/assets/t_piece.o src/assets/s_piece.o src/assets/z_piece.o src/game/asset_manager.o src/game/game_manager.o
	gcc -o main src/main.o src/render/render.o src/test/test.o src/input/input.o src/assets/cube.o src/assets/line.o src/assets/l_piece.o src/assets/j_piece.o src/assets/t_piece.o src/assets/s_piece.o src/assets/z_piece.o src/game/asset_manager.o src/game/game_manager.o -lm

#run the program
run: all
	watch ./main

#clean the files
clean:
	rm -f src/*.o src/render/*.o src/test/*.o src/input/*.o src/assets/*.o src/game/*.o main