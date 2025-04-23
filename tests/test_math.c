#include <stdbool.h>
#include "math_utils.h"
#include <stdio.h>
#include <math.h>


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

int test_mat4_multiply() {
    // Define two input matrices
    mat4 m1 = {
            .m = {
            {1.0, 2.0, 3.0, 4.0},
            {5.0, 6.0, 7.0, 8.0},
            {9.0, 10.0, 11.0, 12.0},
            {13.0, 14.0, 15.0, 16.0}
        }
    };

    mat4 m2 = {
            .m = {
            {16.0, 15.0, 14.0, 13.0},
            {12.0, 11.0, 10.0, 9.0},
            {8.0, 7.0, 6.0, 5.0},
            {4.0, 3.0, 2.0, 1.0}
        }
    };

    // Expected result of A * B
    mat4 expected = {
            .m = {
            {80.0, 70.0, 60.0, 50.0},
            {240.0, 214.0, 188.0, 162.0},
            {400.0, 358.0, 316.0, 274.0},
            {560.0, 502.0, 444.0, 386.0}
        }
    };

    mat4 actual = mat4_multiply(m1, m2);

    if (mat4_equal(actual, expected)) {
        printf("mat4_multiply: PASS\n");
        return 1;
    } else {
        printf("mat4_multiply: FAIL\n");

        printf("Actual:\n");

        mat4_print(actual);

        printf("Expected:\n");

        mat4_print(expected);

        return 0;
    }

}

int test_mat4_identity() {
    mat4 expected = {
                .m = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        }
    };

    mat4 actual = mat4_identity();

    if (mat4_equal(actual, expected)) {
        printf("mat4_identity: PASS\n");
        return 1;
    } else {
        printf("mat4_identity: FAIL\n");

        printf("Actual:\n");

        mat4_print(actual);

        printf("Expected:\n");

        mat4_print(expected);
        return 0;
    }

}

int test_mat4_perspective() {
    float fov = 100.0f,
          aspect = 800.0f / 600.0f,
          near = 0.1f,
          far = 1000.0f;

    
    mat4 actual = mat4_perspective(fov, aspect, near, far);
    mat4 expected = {0};

    
    expected.m[0][0] = 0.62932f;
    expected.m[1][1] = 0.83910f;
    expected.m[2][2] = -1.00020f;
    expected.m[3][2] = -0.20002f;
    expected.m[2][3] = -1.0f;

    int pass = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (fabs(actual.m[i][j] - expected.m[i][j]) >= EPSILON) {
                pass = 0;
            }
        }
    }

    // if (fabs(actual.m[0][0] - expected.m[0][0]) < EPSILON &&
    //     fabs(actual.m[1][1] - expected.m[1][1]) < EPSILON &&
    //     fabs(actual.m[2][2] - expected.m[2][2]) < EPSILON &&
    //     fabs(actual.m[3][2] - expected.m[3][2]) < EPSILON &&
    //     fabs(actual.m[2][3] - expected.m[2][3]) < EPSILON) {
    if(pass) {
        printf("mat4_perspective: PASS\n");

        printf("Actual:\n");

        mat4_print(actual);

        printf("Expected:\n");

        mat4_print(expected);

    } else {
        printf("mat4_perspective: FAIL\n");
        printf("Actual:\n");
        mat4_print(actual);
        printf("Expected:\n");
        mat4_print(expected);
    }
    return pass;
}

int main() {
    test_vec3_add();
    test_vec3_sub();
    test_vec3_scale();
    test_vec3_dot();
    test_vec3_normalize();
    // Call other tests

    test_mat4_multiply();
    test_mat4_identity();
    test_mat4_perspective();

    return 0;
}