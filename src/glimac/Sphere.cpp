#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Sphere.hpp"

namespace glimac {

void Sphere::build(GLfloat r, GLsizei discLat, GLsizei discLong) {
    // Equation paramétrique en (r, phi, theta) de la sphère
    GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
    GLfloat dPhi = 2 * glm::pi<float>() * rcpLat, dTheta = glm::pi<float>() * rcpLong;

    std::vector<ShapeVertex> data;

    // Construit l'ensemble des vertex
    for(GLsizei j = 0; j <= discLong; ++j) {
        GLfloat cosTheta = cos(-glm::pi<float>() / 2 + j * dTheta);
        GLfloat sinTheta = sin(-glm::pi<float>() / 2 + j * dTheta);

        for(GLsizei i = 0; i <= discLat; ++i) {
            ShapeVertex vertex;

            vertex.texCoords.x = i * rcpLat;
            vertex.texCoords.y = 1.f - j * rcpLong;

            vertex.normal.x = sin(i * dPhi) * cosTheta;
            vertex.normal.y = sinTheta;
            vertex.normal.z = cos(i * dPhi) * cosTheta;

            vertex.position = r * vertex.normal;

            data.push_back(vertex);
        }
    }

    m_nVertexCount = discLat * discLong * 6;

    GLuint idx = 0;
    // Construit les vertex finaux en regroupant les données en triangles:
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
    // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    for(GLsizei j = 0; j < discLong; ++j) {
        GLsizei offset = j * (discLat + 1);
        for(GLsizei i = 0; i < discLat; ++i) {
            m_Vertices.push_back(data[offset + i]);
            m_Vertices.push_back(data[offset + (i + 1)]);
            m_Vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
            m_Vertices.push_back(data[offset + i]);
            m_Vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
            m_Vertices.push_back(data[offset + i + discLat + 1]);
        }
    }

    this->initVbo();
    this->initVao();

    // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
    // par un Index Buffer Object, que nous verrons dans les prochains TDs
}

GLuint Sphere::getVbo() {
  return this->vbo;
}

GLuint Sphere::getVao() {
  return this->vao;
}

glm::mat4 Sphere::getModelMatrix() {
  return this->modelMatrix;
}

void Sphere::initVbo() {
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER,this->getVertexCount()*sizeof(ShapeVertex), this->getDataPointer(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Sphere::initVao() {
  glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    const GLuint VERTEX_POSITION_LOCATION = 0;
    const GLuint VERTEX_NORMAL_LOCATION = 1;
    const GLuint VERTEX_TEXTURE_LOCATION = 2;
    glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);
    glEnableVertexAttribArray(VERTEX_NORMAL_LOCATION);
    glEnableVertexAttribArray(VERTEX_TEXTURE_LOCATION);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glVertexAttribPointer(VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) 0);
    glVertexAttribPointer(VERTEX_NORMAL_LOCATION  , 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_TEXTURE_LOCATION , 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, texCoords)));
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void Sphere::draw(Texture * texture, glm::vec3 translate, int time, glm::vec3 rotate, glm::vec3 scale) {
    this->resetMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(texture->getActiveTexture());
    this->modelMatrix = glm::translate(glm::mat4(1), translate);
    // this->modelMatrix = glm::rotate(this->modelMatrix, time, rotate);
    this->modelMatrix = glm::scale(this->modelMatrix, scale);
    glBindTexture(GL_TEXTURE_2D,texture->getidTexture());
}

void Sphere::draw(Texture * texture, int x, int y) {
	  glBindTexture(GL_TEXTURE_2D, 0);
	  glDisable(GL_TEXTURE_2D);
	  glActiveTexture(texture->getActiveTexture());
	  this->modelMatrix = glm::translate(glm::mat4(1), glm::vec3(x, 0, y));
	  this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(0.5, 0.5, 0.5));
	  glBindTexture(GL_TEXTURE_2D,texture->getidTexture());
}

void Sphere::resetMatrix() {
  this->modelMatrix = glm::mat4(1);
}

}

