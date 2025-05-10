#version 330 core

out vec4 color;

uniform float u_time;
uniform vec2 u_resolution;

void main() {
    // Normalizes coordinates
    vec2 uv = gl_FragCoord.xy / u_resolution;
    
    // Centers normalized coordinates vertically
    float centeredY = uv.y - 0.5;

    // Horizontal wave centered
    float wave = sin(uv.x * 20.0 + u_time * 2.0) * 0.1;

    // Add wave to centeredY, then re-normalize
    float y = centeredY + wave + 0.5;

    // Gradient from ocean blue (bottom) to light blue (top)
    vec3 deepBlue = vec3(0.0, 0.1, 0.3);
    vec3 lightBlue = vec3(0.4, 0.7, 1.0);

    vec3 finalColor = mix(deepBlue, lightBlue, y);
    color = vec4(finalColor, 1.0);
}
