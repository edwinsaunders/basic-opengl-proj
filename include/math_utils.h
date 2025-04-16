#ifndef MATH_UTILS_H
#define MATH_UTILS_H

typedef struct {
	float x, y, z;
} vec3;

vec3 vec3_add(vec3 a, vec3 b); // Returns a + b.

vec3 vec3_sub(vec3 a, vec3 b); // Returns a - b.

vec3 vec3_scale(vec3 v, float s); // Scales vector v by scalar s.

float vec3_dot(vec3 a, vec3 b); // Computes dot product.

vec3 vec3_normalize(vec3 v); // Returns normalized vector (unit length).


#endif // MATH_UTILS_H