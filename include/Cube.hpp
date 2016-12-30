#pragma once

#include <vector>

#include "glimac/common.hpp"
#include <GL/glew.h>
#include "Texture.hpp"

namespace glimac {

// Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Cube {
    // Alloue et construit les données (implantation dans le .cpp)
    void build();

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Cube(){
        build(); // Construction (voir le .cpp)
    }

    ~Cube();

    // Renvoit le pointeur vers les données
    const ShapeVertex* getDataPointer() const {
        return &m_Vertices[0];
    }

    // Renvoit le nombre de vertex
    GLsizei getVertexCount() const {
        return m_Vertices.size();
    }

    void initVbo();
    void initVao();
    GLuint getVbo();
    GLuint getVao();
    glm::mat4 getModelMatrix();
    void draw(Texture * texture, int i , int j);
    void draw(Texture * texture, glm::vec3 translate, float radian, glm::vec3 scale);
    void drawPlane(Texture * texture, float scale, float translateX, float translateY);
    void resetMatrix();
    void freeTextures();

private:
    std::vector<ShapeVertex> m_Vertices;
    GLuint vbo;
    GLuint vao;
    glm::mat4 modelMatrix;
};

}
