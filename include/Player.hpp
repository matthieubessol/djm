#pragma once

#include <vector>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include "Terrain.hpp"


namespace glimac {

// Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Player {
private:
    FreeflyCamera * camera;
    int health;
    std::vector<PlayerItem*> items;

    void moov(Terrain *t, float value);

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Player();
    ~Player();

    FreeflyCamera* getCamera();

    int getHealth();
    void setHealth(int _health);
    void moovBack(Terrain *t);
    void moovForward(Terrain *t);
    void lookLeft();
    void lookRight();
    void addItem(PlayerItem *k);
    bool hasItem(PlayerItem *k);
};
}
