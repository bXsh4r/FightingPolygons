build:
	gcc -Iinclude src/*c -lm `pkg-config --cflags sdl3` `pkg-config --libs sdl3` -o program
run:
	./program
