#version 330 core
layout (location = 0) in vec2 vertPos;
layout (location = 1) in vec2 texPos;

out vec2 posTexOut;

uniform mat2 size;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(vertPos * size, 0.0f, 1.0f);
    posTexOut = texPos;
}
