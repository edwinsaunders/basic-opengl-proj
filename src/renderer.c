#include "renderer.h"
#include "glad/glad.h"
#include "shader_path_res.h"
#include <stdio.h>
#include <stdlib.h>

static GLuint shaderProgram;
static GLuint vao, vbo;

char *loadShaderSource(const char *filename) {
	// open file for read (gets pointer to file stream)
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("Error reading file.");
		exit(1);
	}


	// go to end of file to get size
	fseek(fp, 0, SEEK_END);
	
	// store size
	long file_size = ftell(fp);

	// reset fp to beginning of file
	rewind(fp);

	// allocate memory for string making room for null terminator
	char *buffer = malloc(file_size + 1);
	if (buffer == NULL) {
		perror("Error allocating buffer for text.");
		exit(1);
	}

	// read file into buffer string and add null terminator
	fread(buffer, 1, file_size, fp);
	buffer[file_size] = '\0';

	// close file
	fclose(fp);

	return buffer;
}

GLuint createShaderProgram(const char* vertPath, const char* fragPath) {
	GLuint vertShader = glad_glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glad_glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *vertexShaderCode = loadShaderSource(vertPath);
	const GLchar *fragmentShaderCode = loadShaderSource(fragPath);

	glad_glShaderSource(vertShader, 1, &vertexShaderCode, NULL);
	glad_glShaderSource(fragShader, 1, &fragmentShaderCode, NULL);
	glad_glCompileShader(vertShader);
	glad_glCompileShader(fragShader);

	GLuint program = glad_glCreateProgram();
	glad_glAttachShader(program, vertShader);
    glad_glAttachShader(program, fragShader);

    glLinkProgram(program);

    


    // Error checking for compilation
    GLint success;
    GLchar infoLog[512];
    glad_glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glad_glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        printf("Vertex shader compilation failed: %s\n", infoLog);
    } else {
        printf("Vertex shader compilation: Success\n");
    }

    glad_glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glad_glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        printf("Fragment shader compilation failed: %s\n", infoLog);
    } else {
        printf("Fragment shader compilation: Success\n");
    }

    // Error checking for linking
    glad_glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glad_glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("Shader program linking failed: %s\n", infoLog);
    } else {
        printf("Shader program linking: Success\n");
    }

    // cleanup
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    free((void *)vertexShaderCode);
    free((void *)fragmentShaderCode);

	return program;	
}


void initRenderer(void) {
	glViewport(0, 0, 800, 600); // Match window size
	float vertices[] = {
	    -0.5f, -0.5f, // Bottom-left (Triangle 1)
    	 0.5f, -0.5f, // Bottom-right (Triangle 1)
    	 0.5f,  0.5f, // Top-right (Triangle 1)
    	-0.5f, -0.5f, // Bottom-left (Triangle 2)
    	 0.5f,  0.5f, // Top-right (Triangle 2)
    	-0.5f,  0.5f  // Top-left (Triangle 2)
	};

	printf("Vertex data:\n");
    for (int i = 0; i < 12; i += 2) {
        printf("Vertex %d: (%f, %f)\n", i/2, vertices[i], vertices[i+1]);
    }

	glad_glGenVertexArrays(1, &vao);
	glad_glGenBuffers(1, &vbo);

	printf("VAO ID: %u\n", vao);
    printf("VBO ID: %u\n", vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glad_glBindVertexArray(vao);

	glad_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glad_glEnableVertexAttribArray(0);

	printf("VAO ID: %u\n", vao);
	printf("VBO ID: %u\n", vbo);

	char *vertshaderpath = get_shader_path("vertex.glsl");
	char *fragshaderpath = get_shader_path("fragment.glsl");
	shaderProgram = createShaderProgram(vertshaderpath, fragshaderpath);

}

void renderScene(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("OpenGL error in renderScene: %u\n", error);
    }
}