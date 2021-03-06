#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../include/Cube.hpp"
#include "../include/Texture.hpp"

namespace glimac {

void Cube::build() {
    this->modelMatrix = glm::mat4(1);
    float vertices[] = {-1.0, -1.0, -1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1 A B C A D C
                        -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1

                        1.0, -1.0, 1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,       // Face 2
                        1.0, -1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 2

                        -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, -1.0, -1.0,      // Face 3
                        -1.0, -1.0, 1.0,   -1.0, -1.0, -1.0,   1.0, -1.0, -1.0,    // Face 3

                        -1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4
                        -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4

                        -1.0, -1.0, -1.0,   -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,     // Face 5
                        -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   -1.0, 1.0, 1.0,     // Face 5

                        -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 6
                        -1.0, 1.0, 1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0};      // Face 6

    float normals[] = { 0,0,-1,0,0,-1,0,0,-1,
                        0,0,-1,0,0,-1,0,0,-1,

                       1,0,0,1,0,0,1,0,0,
                       1,0,0,1,0,0,1,0,0,

                       0,-1,0,0,-1,0,0,-1,0,
                       0,-1,0,0,-1,0,0,-1,0,

                       0,0,1,0,0,1,0,0,1,
                        0,0,1,0,0,1,0,0,1,

                        0,1,0,0,1,0,0,1,0,
                       0,1,0,0,1,0,0,1,0,

                        0,1,0,0,1,0,0,1,0,
                       0,1,0,0,1,0,0,1,0};      // Face 6
//    float coordTextureTmp[] = { 0, 0,0,   1, 0,0,   1, 1,0,     // Face 1
//                                0, 0,0,   0, 1,0,   1, 1,0,     // Face 1
//
//                                  0, 0,0,   1, 0,0,   1, 1,0,     // Face 2
//                                  0, 0,0,   0, 1,0,   1, 1,0,     // Face 2
//
//                                  0, 0,0,   1, 0,0,   1, 1,0,     // Face 3
//                                  0, 0,0,   0, 1,0,   1, 1,0,     // Face 3
//
//                                  0, 0,0,   1, 0,0,   1, 1,0,     // Face 4
//                                  0, 0,0,   0, 1,0,   1, 1,0,     // Face 4
//
//                                  0, 0,0,   1, 0,0,   1, 1,0,     // Face 5
//                                  0, 0,0,   0, 1,0,   1, 1,0,     // Face 5
//
//                                  0, 0,0,   1, 0,0,   1, 1,0,     // Face 6
//                                  0, 0,0,   0, 1,0,   1, 1,0};    // Face 6

    float coordTextureTmp[] = { 0, 0,0,   0, 1,0,   1, 1,0,     // Face 1
    							0, 0,0,   1, 0,0,   1, 1,0,

								0, 0,0,   0, 1,0,   1, 1,0,     // Face 2
								0, 0,0,   1, 0,0,   1, 1,0,

								0, 0,0,   0, 1,0,   1, 1,0,     // Face 3
								0, 0,0,   1, 0,0,   1, 1,0,

								0, 0,0,   0, 1,0,   1, 1,0,     // Face 4
								0, 0,0,   1, 0,0,   1, 1,0,

								0, 0,0,   0, 1,0,   1, 1,0,     // Face 5
								0, 0,0,   1, 0,0,   1, 1,0,

								0, 0,0,   0, 1,0,   1, 1,0,     // Face 6
								0, 0,0,   1, 0,0,   1, 1,0};


    // Construit l'ensemble des vertex
    for(GLsizei i = 0; i < 108 ; i+=3) {
        ShapeVertex vertex;

        vertex.texCoords.x = coordTextureTmp[i];
        vertex.texCoords.y = coordTextureTmp[i+1];

        vertex.normal.x = normals[i];
        vertex.normal.y = normals[i+1];
        vertex.normal.z = normals[i+2];

        vertex.position.x = vertices[i];
        vertex.position.y = vertices[i+1];
        vertex.position.z = vertices[i+2];

        m_Vertices.push_back(vertex);
    }

    this->initVbo();
    this->initVao();

    // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
    // par un Index Buffer Object, que nous verrons dans les prochains TDs
}

Cube::~Cube() {

}

void Cube::initVbo() {
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER,this->getVertexCount()*sizeof(ShapeVertex), this->getDataPointer(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Cube::initVao() {
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

GLuint Cube::getVbo() {
  return this->vbo;
}

GLuint Cube::getVao() {
  return this->vao;
}

glm::mat4 Cube::getModelMatrix() {
  return this->modelMatrix;
}

void Cube::draw(Texture * texture, int i , int j) {
  //glBindTexture(GL_TEXTURE_2D, 0);
  // glDisable(GL_TEXTURE_2D);
  glActiveTexture(texture->getActiveTexture());
  this->modelMatrix = glm::translate(glm::mat4(1), glm::vec3(i, 0, j));
  this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(0.5, 0.5, 0.5));
  glBindTexture(GL_TEXTURE_2D,texture->getidTexture());
  // glDrawArrays(GL_TRIANGLES,0, this->getVertexCount());
}

void Cube::drawPlane(Texture * texture, float scale, float translateX, float translateY) {
  this->resetMatrix();
  //glBindTexture(GL_TEXTURE_2D, 0);
  //glDisable(GL_TEXTURE_2D);
  glActiveTexture(texture->getActiveTexture());
  this->modelMatrix = glm::translate(glm::mat4(1), glm::vec3(translateX, -0.6, translateY));
  this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(scale,0.1,scale));
  glBindTexture(GL_TEXTURE_2D,texture->getidTexture());
  // glDrawArrays(GL_TRIANGLES,0, this->getVertexCount());
}

void Cube::draw(Texture * texture, glm::vec3 translate, float radian, glm::vec3 scale) {
  this->resetMatrix();
  //glBindTexture(GL_TEXTURE_2D, 0);
  //glDisable(GL_TEXTURE_2D);

  glActiveTexture(texture->getActiveTexture());

  glActiveTexture(texture->getActiveTexture());
  this->modelMatrix = glm::translate(glm::mat4(1), translate);
  this->modelMatrix = glm::rotate(this->modelMatrix, radian, glm::vec3(0, 0, 1));
  this->modelMatrix = glm::scale(this->modelMatrix, scale);
  glBindTexture(GL_TEXTURE_2D,texture->getidTexture());
}

void Cube::resetMatrix() {
  this->modelMatrix = glm::mat4(1);
}

}
