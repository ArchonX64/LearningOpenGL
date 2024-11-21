#version 330 core
in vec2 posTex;

out vec4 color;

uniform sampler2D texture0;
uniform vec3 inColor;

void main() {
    // Only stored in the red component, and we put it in the alpha value
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(texture0, posTex).r);
    color = vec4(inColor, 1.0f) * sampled;
}
