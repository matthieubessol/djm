#version 330 core
in vec3 vPosition_vs;
out vec3 fFragColor;

uniform vec3 uColor;

void main() {
    fFragColor = uColor;
}
