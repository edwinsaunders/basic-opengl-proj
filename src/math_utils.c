// math_utils.c
#include <stdbool.h>
#include <stdio.h>
#include "math_utils.h"
#include <math.h>

// Adds two 3D vectors component-wise, returning a new vector with sum.x = a.x + b.x, etc.
vec3 vec3_add(vec3 a, vec3 b) {
    vec3 sum = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
    return sum;
}

// Subtracts two 3D vectors component-wise, returning a new vector with diff.x = a.x - b.x, etc.
vec3 vec3_sub(vec3 a, vec3 b) {
    vec3 diff = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
    return diff;
}

// Scales a 3D vector by a scalar, multiplying each component by s to stretch or shrink the vector
vec3 vec3_scale(vec3 v, float s) {
    vec3 scaled = {.x = v.x * s, .y = v.y * s, .z = v.z * s};
    return scaled;
}

// Computes the dot product of two 3D vectors, returning a scalar (a.x * b.x + a.y * b.y + a.z * b.z)
float vec3_dot(vec3 a, vec3 b) {
    float dot = a.x * b.x + a.y * b.y + a.z * b.z;
    return dot;
}

// Computes the cross product of two 3D vectors, returning a vector perpendicular to both a and b
// Uses the determinant method: cross.x = a.y * b.z - a.z * b.y, etc.
vec3 vec3_cross(vec3 a, vec3 b) {
    vec3 cross;
    cross.x = a.y * b.z - a.z * b.y;
    cross.y = a.z * b.x - a.x * b.z;
    cross.z = a.x * b.y - a.y * b.x;
    return cross;
}

// Normalizes a 3D vector to unit length by dividing each component by the vector's magnitude
// Magnitude is sqrt(v.x^2 + v.y^2 + v.z^2)
vec3 vec3_normalize(vec3 v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    vec3 normalized = {v.x/length, v.y/length, v.z/length};
    return normalized;
}

// Multiplies two 4x4 matrices, computing result[i][j] as the dot product of row i of a and column j of b
// Combines transformations (e.g., rotation, translation) applied sequentially
mat4 mat4_multiply(mat4 a, mat4 b) {
    mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] +
                             a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
        }
    }
    return result;
}

// Returns a 4x4 identity matrix with 1s on the diagonal and 0s elsewhere
// Represents a transformation that leaves vectors unchanged
mat4 mat4_identity() {
    mat4 result = {0};
    for (int i = 0; i < 4; i++) {        
        result.m[i][i] = 1.0f;        
    }
    return result;
}

// Creates a perspective projection matrix for 3D rendering
// Maps 3D coordinates to a 2D view frustum defined by field of view (fov), aspect ratio, and near/far planes
// Returns identity matrix if inputs are invalid (e.g., far <= near)
mat4 mat4_perspective(float fov, float aspect, float near, float far) {
    mat4 result = {0};
    if (far <= near || aspect <= 0.0f || fov <= 0.0f) {
        printf("Invalid input value(s)...\n");
        result.m[0][0] = 1.0f;
        result.m[1][1] = 1.0f;
        result.m[2][2] = 1.0f;
        result.m[3][3] = 1.0f;
        return result;
    }
    float fovCalc = 1.0f / tanf(fov * 0.5f * (M_PI / 180.0)); // Convert fov to radians and compute scaling factor
    result.m[0][0] = fovCalc / aspect; // Scale X based on aspect ratio
    result.m[1][1] = fovCalc;          // Scale Y based on fov
    result.m[2][2] = -(far + near) / (far - near); // Depth scaling
    result.m[2][3] = -2.0f * far * near / (far - near); // Depth translation
    result.m[3][2] = -1.0f;            // Perspective divide
    return result;
}

// Checks if two 4x4 matrices are equal within a small epsilon
// Compares each element, returning false if any differ by more than EPSILON
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

// Creates a look-at view matrix for the camera
// Orients the camera at position 'eye' looking toward 'target' with 'up' defining the upward direction
// Constructs an orthonormal basis (xaxis, yaxis, zaxis) and translates to camera position
mat4 mat4_look_at(vec3 eye, vec3 target, vec3 up) {
    vec3 zaxis = vec3_normalize(vec3_sub(target, eye)); // Forward: normalize(target - eye)
    vec3 xaxis = vec3_normalize(vec3_cross(up, zaxis)); // Right: normalize(up x forward)
    vec3 yaxis = vec3_cross(zaxis, xaxis);              // Up: forward x right

    mat4 result = {
        .m = {
            { xaxis.x, xaxis.y, xaxis.z, -vec3_dot(xaxis, eye) }, // X-axis and translation
            { yaxis.x, yaxis.y, yaxis.z, -vec3_dot(yaxis, eye) }, // Y-axis and translation
            { zaxis.x, zaxis.y, zaxis.z, -vec3_dot(zaxis, eye) }, // Z-axis and translation
            { 0, 0, 0, 1 }                                       // Homogeneous coordinate
        }
    };
    return result;
}

// Prints a 4x4 matrix for debugging, displaying each element with high precision
void mat4_print(mat4 m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.15f  ", m.m[i][j]);
        }
        printf("\n");
    }
}

// Creates a 4x4 rotation matrix around the X-axis by angle (in radians)
// Rotates vectors in the YZ-plane using cosine and sine functions
mat4 mat4_rotate_x(float angle) {
    mat4 result = mat4_identity();
    float c = cosf(angle);
    float s = sinf(angle);
    result.m[1][1] = c;   // Y scaling
    result.m[1][2] = -s;  // YZ rotation
    result.m[2][1] = s;   // ZY rotation
    result.m[2][2] = c;   // Z scaling
    return result;
}

// Creates a 4x4 rotation matrix around the Y-axis by angle (in radians)
// Rotates vectors in the XZ-plane using cosine and sine functions
mat4 mat4_rotate_y(float angle) {
    mat4 result = mat4_identity();
    float c = cosf(angle);
    float s = sinf(angle);
    result.m[0][0] = c;   // X scaling
    result.m[0][2] = -s;  // XZ rotation
    result.m[2][0] = s;   // ZX rotation
    result.m[2][2] = c;   // Z scaling
    return result;
}

// Creates a 4x4 translation matrix to move vectors by t.x, t.y, t.z
// Adds translation components to the identity matrix
mat4 mat4_translate(vec3 t) {
    mat4 result = mat4_identity();
    result.m[0][3] = t.x; // X translation
    result.m[1][3] = t.y; // Y translation
    result.m[2][3] = t.z; // Z translation
    return result;
}

// Transposes a 4x4 matrix, swapping rows and columns (result[i][j] = a[j][i])
// Useful for converting between row-major and column-major representations
mat4 mat4_transpose(mat4 a) {
    mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = a.m[j][i];
        }
    }
    return result;
}
