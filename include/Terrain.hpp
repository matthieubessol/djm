#pragma once

#include <vector>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include "Pixels.hpp"

namespace glimac {

// Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Terrain {
private:
    std::string path;
    int width;
    int height;
    std::vector<Pixels> pixels;

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Terrain();
    Terrain(std::string _path);
    ~Terrain();
    int getWidth();
    int getHeight();
    std::vector<Pixels> getPixels();
    void loadMap();
};
}
