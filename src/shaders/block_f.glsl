#version 330 core

in vec3 posTexOut;
out vec4 color;

uniform sampler2D texture0;

void main() {
    color = texture(texture0, vec2(posTexOut.x + posTexOut.z, posTexOut.y));
}