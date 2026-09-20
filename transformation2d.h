#ifndef TRANSFORMATION2D_H
#define TRANSFORMATION2D_H

#include "vertex.h"

typedef struct  {
	float matrix[3][3];
} Matrix;

Matrix translation_matrix(float tx, float ty);

Matrix rotaion_matrix(float degree);

Matrix scaling_matrix(float sx, float sy);

void transform(Vertex *vertices, int size, const Matrix *m);


#endif
