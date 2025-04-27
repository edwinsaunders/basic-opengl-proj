#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdbool.h>

#define EPSILON 0.0001f

// Represents a 3D vector with x, y, z components
typedef struct {
    float x, y, z;
} vec3;

// Represents a 4x4 matrix for 3D transformations
typedef struct {
    float m[4][4];
} mat4;

// Adds two 3D vectors component-wise, returning a + b
vec3 vec3_add(vec3 a, vec3 b);

// Subtracts two 3D vectors component-wise, returning a - b
vec3 vec3_sub(vec3 a, vec3 b);

// Scales a 3D vector by a scalar, multiplying each component by s
vec3 vec3_scale(vec3 v, float s);

// Computes the dot product of two 3D vectors (a.x * b.x + a.y * b.y + a.z * b.z)
float vec3_dot(vec3 a, vec3 b);

// Computes the cross product of two 3D vectors, returning a vector perpendicular to a and b
vec3 vec3_cross(vec3 a, vec3 b);

// Normalizes a 3D vector to unit length by dividing by its magnitude
vec3 vec3_normalize(vec3 v);

// Multiplies two 4x4 matrices, combining their transformations (result = a * b)
mat4 mat4_multiply(mat4 a, mat4 b);

// Returns a 4x4 identity matrix (1s on diagonal, 0s elsewhere)
mat4 mat4_identity();

// Creates a perspective projection matrix for 3D rendering, mapping 3D space to a 2D view frustum
mat4 mat4_perspective(float fov, float aspect, float near, float far);

// Creates a look-at view matrix, orienting the camera from eye to target with up direction
mat4 mat4_look_at(vec3 eye, vec3 target, vec3 up);

// Prints a 4x4 matrix for debugging, displaying all 16 elements
void mat4_print(mat4 m);

// Checks if two 4x4 matrices are equal within a small epsilon for floating-point comparison
bool mat4_equal(mat4 a, mat4 b);

// Creates a 4x4 rotation matrix around the X-axis by angle (in radians)
mat4 mat4_rotate_x(float angle);

// Creates a 4x4 rotation matrix around the Y-axis by angle (in radians)
mat4 mat4_rotate_y(float angle);

// Creates a 4x4 translation matrix to move by vector t
mat4 mat4_translate(vec3 t);

// Transposes a 4x4 matrix, swapping rows and columns
mat4 mat4_transpose(mat4 a);

#endif // MATH_UTILS_H
