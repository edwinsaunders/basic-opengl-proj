// renderer.c
#include "renderer.h"
#include "glad/glad.h"
#include "globals.h"
#include "shader_path_res.h"
#include <stdio.h>
#include <stdlib.h>
#include "checkErr.h"

// Static variables for shader program and vertex array/buffer objects
GLuint shaderProgram;
GLuint VAO, VBO;

// Loads shader source code from a file
char *loadShaderSource(const char *filename) {
    // Open file for reading
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error reading file.");
        exit(1);
    }

    // Move to end of file to get size
    fseek(fp, 0, SEEK_END);
    // Store file size
    long file_size = ftell(fp);
    // Reset file pointer to beginning
    rewind(fp);

    // Allocate buffer for file content plus null terminator
    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating buffer for text.");
        exit(1);
    }

    // Read file into buffer and null-terminate
    fread(buffer, 1, file_size, fp);
    buffer[file_size] = '\0';

    // Close file
    fclose(fp);

    return buffer;
}

// Creates and compiles a shader program from vertex and fragment shader files
GLuint createShaderProgram(const char* vertPath, const char* fragPath) {
    // Create vertex and fragment shaders
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load shader source code
    const GLchar *vertexShaderCode = loadShaderSource(vertPath);
    const GLchar *fragmentShaderCode = loadShaderSource(fragPath);

    // Set shader source and compile
    glShaderSource(vertShader, 1, &vertexShaderCode, NULL);
    glShaderSource(fragShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(vertShader);
    glCompileShader(fragShader);

    // Create shader program and attach shaders
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    // Link the program
    glLinkProgram(program);

    // Check vertex shader compilation status
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        printf("Vertex shader compilation failed: %s\n", infoLog);
    } else {
        printf("Vertex shader compilation: Success\n");
    }

    // Check fragment shader compilation status
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        printf("Fragment shader compilation failed: %s\n", infoLog);
    } else {
        printf("Fragment shader compilation: Success\n");
    }

    // Check program linking status
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Shader program linking failed: %s\n", infoLog);
    } else {
        printf("Shader program linking: Success\n");
    }

    // Clean up shaders and source code
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    free((void *)vertexShaderCode);
    free((void *)fragmentShaderCode);

    return program;    
}

// Initializes the renderer: sets up viewport, cube vertices, shaders, and buffers
// void initRenderer(void) {
//     // Set viewport to match window size (800x600)
//     glViewport(0, 0, width, height); // Match window size
//     
//     // Log first 12 vertices for debugging
//     printf("Vertex data (first 12 vertices):\n");
//     for (int i = 0; i < 36; i += 3) {
//         printf("Vertex %d: (%f, %f, %f)\n", i/3, vertices[i], vertices[i+1], vertices[i+2]);
//     }
// 
//     // Generate vertex array and buffer objects
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
// 
//     // Log VAO and VBO IDs for debugging
//     printf("VAO ID: %u\n", VAO);
//     printf("VBO ID: %u\n", VBO);
// 
//     // Bind and upload vertex data to VBO
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 
//     // Bind VAO for vertex attribute setup
//     glBindVertexArray(VAO);
// 
//     // Set position attribute (3 floats per vertex, starting at offset 0)
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     // Set color attribute (3 floats per vertex, starting after position)
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);
// 
//     // Enable depth testing for 3D rendering
//     glEnable(GL_DEPTH_TEST);
// 
//     // Enable back face culling
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);
//     glFrontFace(GL_CCW); // Counter-clockwise winding for front faces
// 
//     
// }

// Renders the scene by drawing the cube
void renderScene(void) {
    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth buffer

    // Activate shader program
    glUseProgram(shaderProgram);
    checkGLError("glUseProgram");
    // Bind vertex array object
    glBindVertexArray(VAO);
    // Draw cube (36 vertices, 12 triangles)
    glDrawArrays(GL_TRIANGLES, 0, 36); // Draw all 36 vertices (12 triangles)
    // Unbind VAO
    glBindVertexArray(0);
}

// Sets mvp matrix as shader uniform (should input mat4 be static?)
void renderer_set_matrix(mat4 mvp) {
    // Pass MVP matrix to shader
    GLuint mvpLoc = glGetUniformLocation(shaderProgram, "mvp");
    if (mvpLoc == -1) {
        printf("Failed to find mvp uniform location\n");
    }
    glUniformMatrix4fv(mvpLoc, 1, GL_TRUE, (float*)mvp.m); // Send MVP matrix (row-major)
    checkGLError("glUniformMatrix4fv");
}