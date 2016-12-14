#pragma once

#include "glm.hpp"

namespace glimac {


class TrackballCamera {
private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

public:
    TrackballCamera();
    void moveFront(float delta); //permet d'avancer / reculer la caméra. Lorsque delta est positif la caméra doit avancer, sinon elle doit reculer.
    void rotateLeft(float degrees); //permet de tourner latéralement autour du centre de vision.
    void rotateUp(float degrees); //permet de tourner verticalement autour du centre de vision.
    glm::mat4 getViewMatrix() const;
};

}
