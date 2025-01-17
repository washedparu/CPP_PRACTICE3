#version 330 core
layout(location = 0) out vec4 color;
uniform float time;
void main() {
    float r = abs(sin(time));
    float g = abs(sin(time + 2.0));
    float b = abs(sin(time + 4.0));
    color = vec4(r, g, b, 1.0);
}
