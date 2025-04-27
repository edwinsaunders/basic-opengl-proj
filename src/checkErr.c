#include "glad/glad.h"
#include <stdio.h>

// Checks for OpenGL errors after an operation and prints any errors found
void checkGLError(const char* operation) {
    GLenum error = glGetError();
    while (error != GL_NO_ERROR) {
        printf("OpenGL error after %s: %d\n", operation, error);
        error = glGetError();
    }
}