#pragma once

#include <vector>
#include <ctime>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include "Terrain.hpp"
#include "SceneElement.h"

using namespace glimac;
//namespace glimac {

// Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Player : public SceneElement{
private:
    FreeflyCamera * camera;
    int nbLife, money;
    clock_t timer;
    std::vector<PlayerItem*> items;

    void moov(Terrain *t, float value);

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Player();
    Player(glm::vec3 pos);
    ~Player();

    void moovBack(Terrain *t);
    void moovForward(Terrain *t);
    void lookLeft();
    void lookRight();
    void addItem(PlayerItem *k);
    bool findAndRemove(PlayerItem *k);
    void addMoney(int value);
    int getMoney();
    int getNbLife();
    int getNbKey();
    void kill();
    glm::vec3 getNextFrontPosition();
    void moveUpdate();
    int getLife();
    bool isDead();
    glm::mat4 getViewMatrix();
    glm::vec3 getFrontVector();
    glm::vec3 getPosition(){return SceneElement::getPosition();}
    void setPosition(glm::vec3 pos);
    void reset();

};
//}
