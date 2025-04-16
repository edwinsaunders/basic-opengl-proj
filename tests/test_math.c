#include "math_utils.h"
#include <stdio.h>
#include <math.h>

#define EPSILON 0.0001f

int test_vec3_add() {
    vec3 a = {1.0f, 2.0f, 3.0f};
    vec3 b = {4.0f, 5.0f, 6.0f};
    vec3 result = vec3_add(a, b);
    if (result.x == 5.0f && result.y == 7.0f && result.z == 9.0f) {
        printf("vec3_add: PASS\n");
        return 1;
    } else {
        printf("vec3_add: FAIL\n");
        return 0;
    }
}

int test_vec3_sub() {
    vec3 a = {1.0f, 2.0f, 3.0f};
    vec3 b = {4.0f, 5.0f, 6.0f};
    vec3 result = vec3_sub(a, b);
    if (result.x == -3.0f && result.y == -3.0f && result.z == -3.0f) {
        printf("vec3_sub: PASS\n");
        return 1;
    } else {
        printf("vec3_sub: FAIL\n");
        return 0;
    }
}

int test_vec3_scale() {
    vec3 v = {1.0f, 2.0f, 3.0f};
    float s = 4.0f;
    vec3 result = vec3_scale(v, s);
    if (result.x == 4.0f && result.y == 8.0f && result.z == 12.0f) {
        printf("vec3_scale: PASS\n");
        return 1;
    } else {
        printf("vec3_scale: FAIL\n");
        return 0;
    }
}

int test_vec3_dot() {
    vec3 a = {1.0f, 2.0f, 3.0f};
    vec3 b = {4.0f, 5.0f, 6.0f};
    float result = vec3_dot(a, b);
    if (result == 32.0f) {
        printf("vec3_dot: PASS\n");
        return 1;
    } else {
        printf("vec3_dot: FAIL\n");
        return 0;
    }
}

int test_vec3_normalize() {
    vec3 v = {1.0f, 2.0f, 3.0f};
    vec3 result = vec3_normalize(v);

    float expected_x = 1.0f/sqrt(14.0f);
    float expected_y = 2.0f/sqrt(14.0f);
    float expected_z = 3.0f/sqrt(14.0f);

    if (fabs(result.x - expected_x) < EPSILON &&
        fabs(result.y - expected_y) < EPSILON &&
        fabs(result.z - expected_z) < EPSILON) {
        printf("vec3_normalize: PASS\n");
        printf("result: %.15f %.15f %.15f\n", result.x, result.y, result.z);
        printf("test: %.15f %.15f %.15f\n", 1.0f/sqrt(14.0f), \
            2.0f/sqrt(14.0f), 3.0f/sqrt(14.0f));
        return 1;
    } else {
        printf("vec3_normalize: FAIL\n");
        
        return 0;
    }
}

int main() {
    test_vec3_add();
    test_vec3_sub();
    test_vec3_scale();
    test_vec3_dot();
    test_vec3_normalize();
    // Call other tests
    return 0;
}