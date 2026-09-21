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

Vertex get_centroid(Vertex *vertices) {
	float x = (vertices[0].x + vertices[1].x + vertices[2].x) / 3.0;
	float y = (vertices[0].y + vertices[1].y + vertices[2].y) / 3.0;

	return (Vertex) {x, y, 0};
}
Matrix rotation_matrix(float degree) {
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

// Currently this only works for rotation
void transform(Vertex *vertices, int size, const Matrix *m) {
	float x, y, rotated_x, rotated_y;
	Vertex centroid = get_centroid(vertices);
	
	for(int i=0; i<size; i++) {
		x = vertices[i].x - centroid.x;
		y = vertices[i].y - centroid.y;

		rotated_x = (m->matrix[0][0] * x) + (m->matrix[0][1] * y) + (m->matrix[0][2]);
		rotated_y = (m->matrix[1][0] * x) + (m->matrix[1][1] * y) + (m->matrix[1][2]);

		vertices[i].x = rotated_x + centroid.x;
		vertices[i].y = rotated_y + centroid.y;
	}	
}
