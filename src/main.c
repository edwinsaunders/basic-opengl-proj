#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "renderer.h"

int main(void) {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("GLFW initialization failed\n");
        return 1;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Explicitly request a color buffer (RGBA with 8 bits each)
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    // Create a window (800x600)
    GLFWwindow* window = glfwCreateWindow(800, 600, "Title", NULL, NULL);
    if (!window) {
        printf("Window creation failed\n");
        glfwTerminate();
        return 1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGL()) {
        printf("GLAD failed to load\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    // Log OpenGL and GLSL versions for debugging
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Check the default framebuffer
    GLint framebuffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
    printf("Default Framebuffer: %d\n", framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Bind default framebuffer
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer incomplete: %u\n", status);
    }

    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Clear any existing OpenGL errors
    while (glGetError() != GL_NO_ERROR);

    // Initialize the renderer
    initRenderer();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Render the scene
        renderScene();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
/*
#include "renderer.h"
#include "glad/glad.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	
	glfwInit();

	GLFWwindow *window = glfwCreateWindow(800, 600, "Title", NULL, NULL);

	if (!window) {
	    printf("Window creation failed\n");
	    glfwTerminate();
	    exit(1);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
	    printf("GLAD failed to load\n");
	    exit(1);
	}

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	// Clear any existing errors
	while (glGetError() != GL_NO_ERROR);

	gladLoadGL();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GLint framebuffer;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
	printf("Default Framebuffer: %d\n", framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Bind default framebuffer
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
	    printf("Framebuffer incomplete: %u\n", status);
	}

	initRenderer();
	glad_glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		glad_glClear(GL_COLOR_BUFFER_BIT);
		renderScene();
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	return 0;
}
*/