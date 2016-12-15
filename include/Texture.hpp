#pragma once

#include <GL/glew.h>

#include "glimac/common.hpp"
#include "Pixels.hpp"

namespace glimac {

// Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Texture {
private:
    int width;
    int height;

public:
    // Constructeur: alloue le tableau de données et construit les attributs des verte;
    Texture(std::string _path);
    ~Texture();
    int getWidth();
    int getHeight();
};
}
