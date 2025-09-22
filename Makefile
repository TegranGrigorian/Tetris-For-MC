# src/command-render/render.h
# src/main.c

#compile the program
all: src/main.o src/command-render/render.o src/test.o src/input-manager/input.o
	gcc -o main src/main.o src/command-render/render.o src/test.o src/input-manager/input.o -lm

#run the program
run: all
	watch ./main

#clean the files
clean:
	rm -f src/*.o src/command-render/*.o main src/test.o src/input-manager/*.o