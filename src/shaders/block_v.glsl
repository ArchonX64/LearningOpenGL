#version 330 core
layout (location = 0) in vec3 posVert;
layout (location = 1) in vec3 posTex;

out vec3 posTexOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(posVert, 1.0);
    posTexOut = posTex;
}
