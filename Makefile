build:
	gcc fightingPolygons.c `pkg-config --cflags sdl3` `pkg-config --libs sdl3` -o fightingPolygons
run:
	./fightingPolygons
