#include "globals.h"

// Camera variables for position (camX, camY, camZ) and orientation (camYaw, camPitch)
float camX = 0.0f, camY = 3.0f, camZ = 5.0f;
float camYaw = 0.0f, camPitch = 0.0f;
float moveSpeed = 0.5f; // Slower for smoother movement
float mouseSensitivity = 0.05f; // Finer mouse control
double lastX = 0.0, lastY = 0.0; // Last mouse position
int firstMouse = 1; // Flag for initial mouse input

// Window dimensions
int width = 1920, height = 1080;

// Vertex data for the cube (positions and colors)
// Defines a room with colored walls: gray floor, white ceiling, red front, green back, blue left, yellow right
float vertices[] = {
    // Floor (gray: 0.5, 0.5, 0.5)
    -ROOM_SIZE, 0.0f, -ROOM_SIZE, 0.5f, 0.5f, 0.5f,
    -ROOM_SIZE, 0.0f, ROOM_SIZE, 0.5f, 0.5f, 0.5f,
    ROOM_SIZE, 0.0f, ROOM_SIZE, 0.5f, 0.5f, 0.5f,
    ROOM_SIZE, 0.0f, ROOM_SIZE, 0.5f, 0.5f, 0.5f,
    ROOM_SIZE, 0.0f, -ROOM_SIZE, 0.5f, 0.5f, 0.5f,
    -ROOM_SIZE, 0.0f, -ROOM_SIZE, 0.5f, 0.5f, 0.5f,

    // Ceiling (white: 1.0, 1.0, 1.0)
    -ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, 1.0f, 1.0f, 1.0f,
    ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, 1.0f, 1.0f, 1.0f,
    ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 1.0f, 1.0f, 1.0f,
    ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 1.0f, 1.0f, 1.0f,
    -ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 1.0f, 1.0f, 1.0f,
    -ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, 1.0f, 1.0f, 1.0f,

    // Front wall (red: 1.0, 0.0, 0.0)
    -ROOM_SIZE, 0.0f, -ROOM_SIZE, 1.0f, 0.0f, 0.0f,
    ROOM_SIZE, 0.0f, -ROOM_SIZE, 1.0f, 0.0f, 0.0f,
    ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, 1.0f, 0.0f, 0.0f,
    ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, 1.0f, 0.0f, 0.0f,
    -ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, 1.0f, 0.0f, 0.0f,
    -ROOM_SIZE, 0.0f, -ROOM_SIZE, 1.0f, 0.0f, 0.0f,

    // Back wall (green: 0.0, 1.0, 0.0)
    -ROOM_SIZE, 0.0f, ROOM_SIZE, 0.0f, 1.0f, 0.0f,
    -ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 0.0f, 1.0f, 0.0f,
    ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 0.0f, 1.0f, 0.0f,
    ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 0.0f, 1.0f, 0.0f,
    ROOM_SIZE, 0.0f, ROOM_SIZE, 0.0f, 1.0f, 0.0f,
    -ROOM_SIZE, 0.0f, ROOM_SIZE, 0.0f, 1.0f, 0.0f,

    // Left wall (blue: 0.0, 0.0, 1.0)
    -ROOM_SIZE, 0.0f, -ROOM_SIZE, 0.0f, 0.0f, 1.0f,
    -ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, 0.0f, 0.0f, 1.0f,
    -ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 0.0f, 0.0f, 1.0f,
    -ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 0.0f, 0.0f, 1.0f,
    -ROOM_SIZE, 0.0f, ROOM_SIZE, 0.0f, 0.0f, 1.0f,
    -ROOM_SIZE, 0.0f, -ROOM_SIZE, 0.0f, 0.0f, 1.0f,

    // Right wall (yellow: 1.0, 1.0, 0.0)
    ROOM_SIZE, 0.0f, -ROOM_SIZE, 1.0f, 1.0f, 0.0f,
    ROOM_SIZE, 0.0f, ROOM_SIZE, 1.0f, 1.0f, 0.0f,
    ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 1.0f, 1.0f, 0.0f,
    ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, 1.0f, 1.0f, 0.0f,
    ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, 1.0f, 1.0f, 0.0f,
    ROOM_SIZE, 0.0f, -ROOM_SIZE, 1.0f, 1.0f, 0.0f
};