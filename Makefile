# src/command-render/render.h
# src/main.c

#compile the program
all: src/main.o src/command-render/render.o
	gcc -o main src/main.o src/command-render/render.o -lm

#run the program
run: all
	watch ./main

