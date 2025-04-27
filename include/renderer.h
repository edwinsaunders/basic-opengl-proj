#ifndef RENDERER_H
#define RENDERER_H

#include "math_utils.h"
#include <glad/glad.h>

void initRenderer(void);
void renderScene(void);
void renderer_set_matrix(mat4 mvp);
GLuint createShaderProgram(const char* vertPath, const char* fragPath);


#endif // RENDERER_H
