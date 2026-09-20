build:
	gcc window.c draw.c transformation2d.c -lm `pkg-config --cflags sdl3` `pkg-config --libs sdl3` -o program
run:
	./program
