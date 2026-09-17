#include <stdio.h>
#include <stdint.h>

int main() {
	uint8_t r = 0x12;
	uint8_t g = 0x3A;
	uint8_t b = 0xF9;

	uint32_t rgb = (r << 16) | (g << 8) | b; 

	printf("%x", rgb);

}
