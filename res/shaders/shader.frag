#version 330 core

out vec4 color;

uniform float u_time;
uniform vec2 u_resolution;

void main() {
    // Convert to Normalized Device Coordinates: (-1 to +1)
    vec2 ndc = (gl_FragCoord.xy / u_resolution) * 2.0 - 1.0;

    // Maintain aspect ratio by scaling x
    ndc.x *= u_resolution.x / u_resolution.y;

    // Centered sine wave (horizontal)
    float wave = sin(ndc.x * 10.0 + u_time * 2.0) * 0.1;

    // Gradient blend from deep ocean blue to light blue based on vertical position
    float y = ndc.y + wave;

    vec3 deepBlue = vec3(0.0, 0.1, 0.3);
    vec3 lightBlue = vec3(0.4, 0.7, 1.0);

    // Map y from [-1, 1] to [0, 1] for mixing
    float gradient = clamp((y + 1.0) * 0.5, 0.0, 1.0);

    vec3 finalColor = mix(deepBlue, lightBlue, gradient);
    color = vec4(finalColor, 1.0);
}
