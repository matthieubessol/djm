#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vColor;

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;

// Sorties du shader
out vec3 vPosition_vs; // Position du sommet transformé dans l'espace View

void main() {
    // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1);

    // Calcul des valeurs de sortie
    vPosition_vs = vec3(uMVMatrix * vertexPosition);

    // Calcul de la position projetée
    gl_Position = uMVPMatrix * vertexPosition;
}
