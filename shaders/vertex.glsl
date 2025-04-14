#version 330 core
layout(location = 0) in vec2 aPos; // Input vertex position (matches VBO)
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0); // Output position (2D to 4D)
}