#include "window.h"
#include "draw.h"

#include <stdint.h>

int main(void) {	
	
	int width = 1280;
	int height = 800;
	uint32_t framebuffer[width * height];

	draw_init(framebuffer, width, height);

	if(create_window(framebuffer, width, height) == 1) 
		return 1;

	return 0;
}
