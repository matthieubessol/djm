#pragma once

#include <vector>
#include <ctime>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include "Terrain.hpp"
#include "SceneElement.h"

using namespace glimac;

class Player : public SceneElement{
private:
    FreeflyCamera * camera;
    int nbLife, money;
    clock_t timer;
    std::vector<PlayerItem*> items;

    void moov(Terrain *t, float value);

public:
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
    void increaseLife(){nbLife++;}
    void resetMoney(){money = 0;}

};
