#include <stdbool.h>
#include <stdio.h>
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

// Multiplies two 4x4 matrices.
mat4 mat4_multiply(mat4 a, mat4 b) {
	mat4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + \
							 a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
		}
	}
	return result;
}

// Returns a 4x4 identity matrix.
mat4 mat4_identity() {
	mat4 result = {0};
	for (int i = 0; i < 4; i++) {		
		result.m[i][i] = 1.0f;		
	}
	return result;
}

// Creates a perspective projection matrix (used for 3D viewing).
mat4 mat4_perspective(float fov, float aspect, float near, float far) {
	mat4 result = {0};
	float fovCalc = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);
	result.m[0][0] = aspect * fovCalc;
	result.m[1][1] = fovCalc;
	result.m[2][2] = far / (far - near);
	result.m[3][2] = (-1.0f) * far * near / (far - near);
	result.m[2][3] = 1.0f;
	return result;
}

bool mat4_equal(mat4 a, mat4 b) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fabs(a.m[i][j] - b.m[i][j]) >= EPSILON) {
				return false;
			}
		}
	}
	return true;
}

// print a matrix
void mat4_print(mat4 m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.15f  ", m.m[i][j]);
		}
		printf("\n");
	}
}