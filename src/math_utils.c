#include "math_utils.h"
#include <math.h>

// Returns a + b.
vec3 vec3_add(vec3 a, vec3 b) {
	vec3 sum = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
	return sum;
}

// Returns a - b.
vec3 vec3_sub(vec3 a, vec3 b) {
	vec3 diff = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
	return diff;
}

// Scales vector v by scalar s.
vec3 vec3_scale(vec3 v, float s) {
	vec3 scaled = {.x = v.x * s, .y = v.y * s, .z = v.z * s};
	return scaled;
}

// Computes dot product.
float vec3_dot(vec3 a, vec3 b) {
	float dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return dot;
}

// Returns normalized vector (unit length).
vec3 vec3_normalize(vec3 v) {
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	vec3 normalized = {v.x/length, v.y/length, v.z/length};
	return normalized;
}