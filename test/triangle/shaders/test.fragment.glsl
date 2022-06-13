#version 330 core

out vec3 color;

uniform vec2 screenSize;

void main() {
    color.xy = gl_FragCoord.xy / screenSize.xy;
}
