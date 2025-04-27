#ifndef CALLBACKFUNCS_H
#define CALLBACKFUNCS_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void framebufferSizeCallback(GLFWwindow* window, int w, int h);

#endif // CALLBACKFUNCS_H