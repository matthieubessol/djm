#pragma once

#include <vector>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"

namespace glimac {

// Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Player {
private:
    FreeflyCamera * camera;
    int health;

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Player();
    ~Player();

    FreeflyCamera* getCamera();

    int getHealth();
    void setHealth(int _health);
};
}
