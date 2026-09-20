#ifndef DRAW_H
#define DRAW_H

#include "vertex.h"

#include <stdbool.h>

void draw_init(uint32_t *fb, int w, int h);

void put_pixel(int x, int y, uint32_t color);

void draw_line(int x0, int y0, uint32_t colorA, int x1, int y1, uint32_t colorB);

void draw_rect(int x, int y, int width, int height, uint32_t color, bool fill);

void draw_tri(Vertex point1, Vertex point2, Vertex point3, bool fill);


#endif
