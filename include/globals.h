#ifndef GLOBALS_H
#define GLOBALS_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

// Camera variables for position (camX, camY, camZ) and orientation (camYaw, camPitch)
extern float camX, camY, camZ;
extern float camYaw, camPitch;
extern float moveSpeed; // Slower for smoother movement
extern float mouseSensitivity; // Finer mouse control
extern double lastX, lastY; // Last mouse position
extern int firstMouse; // Flag for initial mouse input

// Room dimensions (cube with side length 2 * ROOM_SIZE)
#define ROOM_SIZE 10.0f

// Window dimensions
extern int width, height;

// GLFW window handle
extern GLFWwindow* window;

// OpenGL shader program ID
extern GLuint shaderProgram;

// Vertex Array Object and Vertex Buffer Objects for rendering
extern GLuint VAO, VBO;

// Vertex data for the cube (positions and colors)
// Defines a room with colored walls: gray floor, white ceiling, red front, green back, blue left, yellow right
extern float vertices[216];

#endif // GLOBALS_H