#pragma once

#include "glm.hpp"

namespace glimac {


class FreeflyCamera {

public:
    FreeflyCamera();
    void moveFront(float t);
	void moveLeft(float t);
    void rotateLeft(float degrees);
    void rotateRight(float degrees);
    void rotateUp(float degrees);
    void computeDirectionVectors();
    glm::mat4 getViewMatrix() const;
    void setPosition(glm::vec3 _position);
    glm::vec3 getPosition();
    glm::vec3 getFuturePosition(float value);
    float getMoveFrontValue();
    float getAngleValue();
    glm::vec3 getFrontVector();
    void updateRotation();
    void updateMoving();
    void setIsLeft(bool _isLeft);
    void setIsForward(bool _isForward);
    void setIsMoving(bool _isMoving);
    void setIsTurning(bool _isTurning);
    bool getIsTurning();
    bool getIsMoving();
    void resetValues();

private:
	float m_fPhi;
	float m_fTheta;
	glm::vec3 m_Position;
	glm::vec3 m_FrontVector;
	glm::vec3 m_LeftVector;
	glm::vec3 m_UpVector;
    float moveFrontValue;
    float angleValue;

    bool isTurning;
    bool isLeft;
    bool isMoving;
    bool isForward;
    float forwardMovingValue;
    float angleMovingValue;

};

}
