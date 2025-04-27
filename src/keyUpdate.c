#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "globals.h"
#include <math.h>
#include "math_utils.h"
#include <stdio.h>

void processInput(GLFWwindow* window) {
    float yawRad = camYaw * M_PI / 180.0f; // Convert yaw to radians
    float pitchRad = camPitch * M_PI / 180.0f; // Convert pitch to radians

    // Compute forward direction (matches View matrix target - eye)
    // Uses spherical coordinates based on yaw and pitch
    vec3 forward = {
        cosf(pitchRad) * sinf(yawRad),
        -sinf(pitchRad),
        cosf(pitchRad) * cosf(yawRad)
    };
    forward = vec3_normalize(forward); // Normalize to unit length

    // Compute right direction (perpendicular to forward and world up)
    vec3 up = { 0.0f, 1.0f, 0.0f };
    vec3 right = vec3_normalize(vec3_cross(forward, up));

    // Compute movement direction in view space (XZ plane)
    vec3 moveDir = { 0.0f, 0.0f, 0.0f };
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        // Move forward (opposite forward vector, toward camera's look direction)
        moveDir.x -= forward.x * moveSpeed;
        moveDir.z -= forward.z * moveSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        // Move backward (along forward vector, away from look direction)
        moveDir.x += forward.x * moveSpeed;
        moveDir.z += forward.z * moveSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        // Strafe left (along right vector)
        moveDir.x += right.x * moveSpeed;
        moveDir.z += right.z * moveSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        // Strafe right (opposite right vector)
        moveDir.x -= right.x * moveSpeed;
        moveDir.z -= right.z * moveSpeed;
    }

    // Update camera position
    camX += moveDir.x;
    camY += moveDir.y; // No vertical movement
    camZ += moveDir.z;

    // Enforce collision with room boundaries
    if (camX < -ROOM_SIZE + 0.5f) camX = -ROOM_SIZE + 0.5f; // Left wall
    if (camX > ROOM_SIZE - 0.5f) camX = ROOM_SIZE - 0.5f;   // Right wall
    if (camZ < -ROOM_SIZE + 0.5f) camZ = -ROOM_SIZE + 0.5f; // Front wall
    if (camZ > ROOM_SIZE - 0.5f) camZ = ROOM_SIZE - 0.5f;   // Back wall
    if (camY < 0.5f) camY = 0.5f;                           // Floor
    if (camY > ROOM_SIZE - 0.5f) camY = ROOM_SIZE - 0.5f;   // Ceiling

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1); // Close window on ESC
    }

    // Print camera state for debugging
    printf("camX: %f, camY: %f, camZ: %f, camYaw: %f, camPitch: %f\n", camX, camY, camZ, camYaw, camPitch);
}