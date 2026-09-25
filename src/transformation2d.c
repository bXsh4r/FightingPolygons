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
		{cos(rad), -sin(rad)},
		{sin(rad), cos(rad)}
	}};
}

Matrix scaling_matrix(float sx, float sy) {
	return (Matrix) {{
		{sx, 0},
		{0, sy}
	}};
}

// For rotation and scaling
void linear_transform(Vertex *vertices, int size, const Matrix *m) {
	float x, y, transformed_x , transformed_y;
	Vertex centroid = get_centroid(vertices); // get the centroid of the triangle, subtract it from it original vertices will get you new vertices with origin (0,0) centroid. 
						  // rotate. then add the centroid back to move the triangle back to its original place.
						  // otherwise the triangle will rotate around (0,0) not around itself.
	
	for(int i=0; i<size; i++) {
		x = vertices[i].x - centroid.x;
		y = vertices[i].y - centroid.y;

		transformed_x = (m->matrix[0][0] * x) + (m->matrix[0][1] * y);
		transformed_y = (m->matrix[1][0] * x) + (m->matrix[1][1] * y);

		vertices[i].x = transformed_x + centroid.x;
		vertices[i].y = transformed_y + centroid.y;
	}	
}

// For translation
void affline_transform(Vertex *vertices, Vertex *original_vertices, int size, const Matrix *m, int screen_width) {	
	float x, y;
	
	for(int i=0; i<size; i++) {
		x = vertices[i].x;
		y = vertices[i].y;

		vertices[i].x = (m->matrix[0][0] * x) + (m->matrix[0][1] * y) + (m->matrix[0][2]);
		vertices[i].y = (m->matrix[1][0] * x) + (m->matrix[1][1] * y) + (m->matrix[1][2]);

		// maps back to original with current vertices offset
		if(vertices[i].x >= (screen_width+original_vertices[i].x)) {
			vertices[0].x = (vertices[0].x - screen_width);
			vertices[1].x = (vertices[1].x - screen_width);
			vertices[2].x = (vertices[2].x - screen_width);
		}
		else if(fabs(vertices[i].x) >= (screen_width+original_vertices[i].x)) {
			vertices[0].x = (fabs(vertices[0].x) - screen_width)*-1.0f;
			vertices[1].x = (fabs(vertices[1].x) - screen_width)*-1.0f;
			vertices[2].x = (fabs(vertices[2].x) - screen_width)*-1.0f;
		}		
	}	
}
