#ifndef CALLBACKFUNCS_H
#define CALLBACKFUNCS_H

#include "glad/glad.h"
#ifdef _WIN32
#include "GLFW/glfw3.h"
#else
#include <GLFW/glfw3.h>
#endif

#include "globals.h"
#include <stdio.h>

void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void framebufferSizeCallback(GLFWwindow* window, int w, int h);

#endif // CALLBACKFUNCS_H