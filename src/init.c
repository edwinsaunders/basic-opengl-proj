#include <glad/glad.h>
#include "renderer.h"
#include "shader_path_res.h"
#include <stdlib.h>
#include "globals.h"
#include "checkErr.h"

// Initializes vertex buffers and vertex array object for rendering the room
void _initBuffers() {
    // Generate VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Load vertex data

    // Set vertex attribute pointers (position and color)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color
    glEnableVertexAttribArray(1);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    checkGLError("_initBuffers");
}

// Initializes OpenGL settings, including depth testing, background color, shaders, and buffers
void initOpenGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for correct 3D rendering
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set background to dark gray


    // Load and compile vertex and fragment shaders
    char *vertshaderpath = get_shader_path("vertex.glsl");
    char *fragshaderpath = get_shader_path("fragment.glsl");
    
    shaderProgram = createShaderProgram(vertshaderpath, fragshaderpath); // Create shader program
    _initBuffers(); // Set up vertex buffers
    
    // Free shader file paths
    free(vertshaderpath);
    free(fragshaderpath);
}