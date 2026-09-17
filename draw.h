#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>
#include <stdbool.h>

void draw_init(uint32_t *fb, int w, int h);

typedef struct {
	int x;
	int y;
} Point;

void put_pixel(int x, int y, uint32_t color);

void draw_line(int x0, int y0, int x1, int y1, uint32_t color);

void draw_rect(int x, int y, int width, int height, uint32_t color, bool fill);

void draw_tri(Point point1, Point point2, Point point3, uint32_t color, bool fill);


#endif
