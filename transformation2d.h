#ifndef TRANSFORMATION2D_H
#define TRANSFORMATION2D_H

#include "vertex.h"

typedef struct  {
	float matrix[3][3];
} Matrix;

Matrix translation_matrix(float tx, float ty);

Matrix rotation_matrix(float degree);

Matrix scaling_matrix(float sx, float sy);

void linear_transform(Vertex *vertices, int size, const Matrix *m);

void affline_transform(Vertex *vertices, Vertex *original_vertices, int size, const Matrix *m, int screen_width);

#endif
