#version 330 core

layout(location = 0) out vec4 color;

uniform float u_color;

void main() {
    float r = abs(sin(u_color));
    float g = abs(sin(u_color + 2.0));
    float b = abs(sin(u_color + 4.0));
    color = vec4(r, g, b, 1.0);
}
