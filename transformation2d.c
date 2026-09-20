#include "transformation2d.h"

#include <stdio.h>
#include <math.h>

Matrix translation_matrix(float tx, float ty) {
	return (Matrix) {{
		{1, 0, tx},
		{0, 1, ty},
		{0, 0, 1}
	}};
}

Matrix rotaion_matrix(float degree) {
	float rad = degree * M_PI / 180;

	return (Matrix) {{
		{cos(rad), -sin(rad), 0},
		{sin(rad), cos(rad), 0},
		{0, 0, 1}
	}};
}

Matrix scaling_matrix(float sx, float sy) {
	return (Matrix) {{
		{sx, 0, 0},
		{0, sy, 0},
		{0, 0, 1}
	}};
}

void transform(Vertex *vertices, int size, const Matrix *m) {
	int x, y;
	for(int i=0; i<size; i++) {
		x = vertices[i].x;
		y = vertices[i].y;

		vertices[i].x = (m->matrix[0][0] * x) + (m->matrix[0][1] * y) + (m->matrix[0][2]);
		vertices[i].y = (m->matrix[1][0] * x) + (m->matrix[1][1] * y) + (m->matrix[1][2]);
	}	
}
