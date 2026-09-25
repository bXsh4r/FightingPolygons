#include "draw.h"

#include <stdlib.h>
#include <string.h>

static uint32_t *framebuffer;	
static int width;
static int height;

void draw_init(uint32_t *fb, int w, int h) {
	framebuffer = fb;
	width = w;
	height = h;
}

void put_pixel(int x, int y, uint32_t color) {

	if(y >= height || y < 0 || width * y + x >= width * height || width * y + x < 0)
		return;

	framebuffer[width * y + x] = color;
}



/*
	Bresenham's line drawing Algorithm

	basically what we are trying to do is get p which is the current y position on the line (x position multiplied by the slope)
	then we check if its closer to y or y+1 and draw a pixel accordingly.

	Bresenham eliminates the need for calculating the slop which might introduce floating numbers. 

	but its the same idea written in a different way.
*/

uint32_t scaleColor(uint32_t color, float t) {

	uint8_t r = color >> 16;
	uint8_t g = color >> 8;
	uint8_t b = color;

	r *= t;
	g *= t;
	b *= t;

	return (r << 16) | (g << 8) | b;
}

uint32_t lerp(int p0, uint32_t colorA, int p1, uint32_t colorB, int pTarget, bool reverse) {
	float t = (float)(pTarget - p0) / (p1 - p0);
	
	if(!reverse)	
		return scaleColor(colorA, 1-t) + scaleColor(colorB, t);	
	return scaleColor(colorA, t) + scaleColor(colorB, 1-t);
}

void draw_line_H(int x0, int y0, uint32_t colorA, int x1, int y1, uint32_t colorB) {
	
	bool reverse = false;
	
	if(x0 > x1) {
		int temp = x0;
		x0 = x1;
		x1 = temp;

		temp = y0;
		y0 = y1;
		y1 = temp;

		reverse = true;
	}	

	int dx = x1 - x0;
	int dy = y1 - y0;

	int dir = dy < 0 ? -1 : 1;
	dy *= dir;
	
	
	int y = y0;
	int p = 2*dy - dx;
	uint32_t color;

	for(int i = 0; i <= dx; i++) {
		color = lerp(x0, colorA, x1, colorB, x0+i, reverse);
		put_pixel(x0 + i, y, color);

		if(p >= 0) {
			y += dir;
			p = p - 2*dx;
		}
		p = p + 2*dy;
	}
}

void draw_line_V(int x0, int y0, uint32_t colorA, int x1, int y1, uint32_t colorB) {

	bool reverse = false;

	if(y0 > y1) {
		int temp = x0;
		x0 = x1;
		x1 = temp;

		temp = y0;
		y0 = y1;
		y1 = temp;

		reverse = true;
	}

	int dx = x1 - x0;
	int dy = y1 - y0;

	int dir = dx < 0 ? -1 : 1;
	dx *= dir;
	
	int x = x0;
	int p = 2*dx - dy;
	uint32_t color;

	for(int i = 0; i <= dy; i++) {
		color = lerp(y0, colorA, y1, colorB, y0+i, reverse);
		put_pixel(x, y0 + i, color);

		if(p >= 0) {
			x += dir;
			p = p - 2*dy;
		}
		p = p + 2*dx;
	}
}

void draw_line(int x0, int y0, uint32_t colorA, int x1, int y1, uint32_t colorB) {
	if(abs(x1 - x0) > abs(y1 - y0)) {
		draw_line_H(x0, y0, colorA, x1, y1, colorB);
	}
	else {
		draw_line_V(x0, y0, colorA, x1, y1, colorB);
	}
}	


/* Lets currently focus on drawing a triangle

void draw_rect(int x, int y, int width, int height, uint32_t color, bool fill) {
	int x1 = x + width;
	int y1 = y + height;
	
	draw_line(x, y, x1, y, color);
	draw_line(x1, y, x1, y1, color);
	draw_line(x1, y1, x, y1, color);
	draw_line(x, y1, x, y, color);
	
	if(fill == true) {
		for(int i=y+1; i<y+height; i++) {
			draw_line(x, i, x1, i, color);	
		}
	}
}
*/


int min(int n0, int n1) {
	if(n0 < n1)
		return n0;
	return n1;
}

int max(int n0, int n1) {
	if(n0 > n1)
		return n0;
	return n1;
}

void draw_tri(Vertex point1, Vertex point2, Vertex point3, bool fill) {
	draw_line(point1.x, point1.y, point1.color, point2.x, point2.y, point2.color);
	draw_line(point2.x, point2.y, point2.color, point3.x, point3.y, point3.color);
	draw_line(point1.x, point1.y, point1.color, point3.x, point3.y, point3.color);

	if(fill == true) {
		int closestX = min(min(point1.x, point2.x), point3.x);
		int closestY = min(min(point1.y, point2.y), point3.y);
		int farthestX = max(max(point1.x, point2.x), point3.x);
		int farthestY = max(max(point1.y, point2.y), point3.y);

		Vertex vertices[farthestX - closestX];
          	int index;

		for(int y=closestY; y<farthestY; y++) {
			memset(vertices, 0, sizeof(int) * (farthestX - closestX));
			index = 0;

			for(int x=closestX; x<=farthestX; x++) {

				if(y >= height || y < 0 || width * y + x >= width * height || width * y + x < 0)
					continue;

				if(framebuffer[width * y + x] != 0) {
					vertices[index].x = x;
					vertices[index].color = framebuffer[width * y + x];
					index++;
				}
			}	
		
			
			int x0;
			int x1;
			uint32_t colorA;
			uint32_t colorB;
			bool found = false;

			for(int i=1; i<index; i++){
				if(vertices[i].x - vertices[i-1].x > 1) {
					x0 = vertices[i-1].x;
					colorA = vertices[i-1].color;

					x1 = vertices[i].x;
					colorB = vertices[i].color;

					found = true;
					break;
				}						
			}
			
			if(found)
				draw_line(x0, y, colorA, x1, y, colorB);					
		}
	}
}
