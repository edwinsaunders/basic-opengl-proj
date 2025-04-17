#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdbool.h>

#define EPSILON 0.0001f

typedef struct {
	float x, y, z;
} vec3;

typedef struct {
	float m[4][4];
} mat4;

vec3 vec3_add(vec3 a, vec3 b); // Returns a + b.

vec3 vec3_sub(vec3 a, vec3 b); // Returns a - b.

vec3 vec3_scale(vec3 v, float s); // Scales vector v by scalar s.

float vec3_dot(vec3 a, vec3 b); // Computes dot product.

vec3 vec3_normalize(vec3 v); // Returns normalized vector (unit length).

// Multiplies two 4x4 matrices.
mat4 mat4_multiply(mat4 a, mat4 b);

// Returns a 4x4 identity matrix.
mat4 mat4_identity();

// Creates a perspective projection matrix (used for 3D viewing).
mat4 mat4_perspective(float fov, float aspect, float near, float far);

// print a matrix
void mat4_print(mat4 m);

bool mat4_equal(mat4 a, mat4 b);

#endif // MATH_UTILS_H