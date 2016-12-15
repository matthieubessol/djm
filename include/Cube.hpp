#pragma once

#include <vector>

#include "glimac/common.hpp"
#include <GL/glew.h>

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

private:
    std::vector<ShapeVertex> m_Vertices;
    GLuint vbo;
    GLuint vao;
};

}
