// main.c
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include "renderer.h"
#include "globals.h"
#include "callbackFuncs.h"
#include "init.h"
#include "keyUpdate.h"


// Main entry point for the program
int main(void) {
    // Initialize GLFW library
    if (!glfwInit()) {
        printf("GLFW initialization failed\n");
        return 1;
    }

    // Configure OpenGL context to use version 3.3, core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Request 8-bit RGBA color buffer
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    // Create a window with title
    GLFWwindow* window = glfwCreateWindow(width, height, "First-Person Room Simulation", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Set up OpenGL context in window
    glfwMakeContextCurrent(window);

    // Initialize GLAD to load OpenGL functions
    if (!gladLoadGL()) {
        printf("GLAD failed to load\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    // Initialize camera at position (0, 0, 5) with zero yaw and pitch
    // Camera cam;
    // camera_init(&cam, (vec3){0.0f, 0.0f, 5.0f}, 0.0f, 0.0f); // Start 5 units back

    // Variables for delta time calculation
    // double current_time;
    // static double last_time = 0.0;
    // float delta_time;

    // Set callbacks and input mode
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Capture mouse


    // Log OpenGL and GLSL versions for debugging
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Initialize OpenGL
    initOpenGL();

    // Verify default framebuffer status
    // GLint framebuffer;
    // glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
    // printf("Default Framebuffer: %d\n", framebuffer);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0); // Bind default framebuffer
    // GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    // if (status != GL_FRAMEBUFFER_COMPLETE) {
    //     printf("Framebuffer incomplete: %u\n", status);
    // }
 
    // // Set clear color to black
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 
    // // Clear any pre-existing OpenGL errors
    // while (glGetError() != GL_NO_ERROR);
 
    // // Initialize renderer (sets up shaders, VAO, VBO)
    // initRenderer();

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time for smooth movement
        // current_time = glfwGetTime();
        // delta_time = (float)(current_time - last_time);
        // last_time = current_time;

        processInput(window); // Update (Handle keyboard input)
        
        // Clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Compute Model-View-Projection (MVP) matrix
        mat4 model = mat4_identity(); // No model transformation
        mat4 view;
        vec3 eye = { camX, camY, camZ }; // Camera position
        float yawRad = camYaw * M_PI / 180.0f; // Yaw in radians
        float pitchRad = camPitch * M_PI / 180.0f; // Pitch in radians
        // Compute look-at target based on yaw and pitch
        vec3 target = {
            camX + cosf(pitchRad) * sinf(yawRad),
            camY - sinf(pitchRad),
            camZ + cosf(pitchRad) * cosf(yawRad)
        };
        vec3 up = { 0.0f, 1.0f, 0.0f }; // World up vector
        view = mat4_look_at(eye, target, up); // Create view matrix
        mat4 projection = mat4_perspective(60.0f, (float)width / height, 0.1f, 100.0f); // Create projection matrix
        printf("Projection matrix:\n");
        mat4_print(projection);
        mat4 temp = mat4_multiply(view, model); // Combine view and model
        mat4 mvp = mat4_multiply(projection, temp); // Combine projection with view-model

        // Print matrices for debugging
        printf("View matrix:\n");
        mat4_print(view);
        printf("MVP matrix:\n");
        mat4_print(mvp);
        
        // Pass MVP matrix to shader
        renderer_set_matrix(mvp);

        // Render the scene (draws cube)
        renderScene();

        // Swap front and back buffers and process events
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Log camera position for debugging
        printf("Camera Pos: (%.2f, %.2f, %.2f)\n", camX, camY, camZ);
    }

    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
