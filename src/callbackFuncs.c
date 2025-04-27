#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "globals.h"
#include <stdio.h>

// Handles mouse movement to update camera yaw and pitch
// Mouse right/left adjusts yaw, up/down adjusts pitch
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = 0; // Initialize mouse position
    }

    double dx = xpos - lastX; // Change in X position
    double dy = lastY - ypos; // Change in Y position (reversed for FPS pitch)

    // Update yaw (horizontal rotation) and pitch (vertical rotation)
    camYaw -= dx * mouseSensitivity; // Right movement decreases yaw
    camPitch += dy * mouseSensitivity; // Down movement increases pitch

    // Clamp pitch to prevent flipping at poles
    if (camPitch > 89.0f) camPitch = 89.0f;
    if (camPitch < -89.0f) camPitch = -89.0f;

    lastX = xpos;
    lastY = ypos;

    // Print orientation for debugging
    printf("camYaw: %f, camPitch: %f\n", camYaw, camPitch);
}

// Updates viewport when window is resized
void framebufferSizeCallback(GLFWwindow* window, int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h); // Set new viewport dimensions
}