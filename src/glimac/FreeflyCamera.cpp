
#include "math.hpp"
#include <iostream>
#include "glimac/glm.hpp"
#include "glimac/FreeflyCamera.hpp"

namespace glimac {

    FreeflyCamera::FreeflyCamera() : m_Position(glm::vec3(0,0,0)), m_fTheta(0){
    	m_fPhi = M_PI;
        moveFrontValue = 1;
        forwardMovingValue = 0;
        angleValue = 90;
        isTurning = false;
        isMoving = false;
        FreeflyCamera::computeDirectionVectors();
    }

    void FreeflyCamera::moveFront(float t){
        m_Position += t * m_FrontVector;
    }

    void FreeflyCamera::moveLeft(float t){
        m_Position += t * m_LeftVector;
    }

    void FreeflyCamera::rotateLeft(float degrees){
        float radians = degrees / 180 * M_PI;
        m_fPhi += radians;
        std::cout<<"PHI "<< m_fPhi<<std::endl;
        FreeflyCamera::computeDirectionVectors();
    }

    void FreeflyCamera::rotateRight(float degrees){
    	rotateLeft(-degrees);
    }

    void FreeflyCamera::rotateUp(float degrees){
        float radians = degrees / 180 * M_PI;
        m_fTheta += radians;

        FreeflyCamera::computeDirectionVectors();
    }

    void FreeflyCamera::computeDirectionVectors(){
        m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
        m_LeftVector = glm::vec3(sin(m_fPhi+(M_PI*0.5)), 0, cos(m_fPhi+(M_PI*0.5)));
        m_UpVector = glm::cross(m_FrontVector, m_LeftVector);

    }

    glm::vec3 FreeflyCamera::getFrontVector() {
        return m_FrontVector;
    }

    void FreeflyCamera::setPosition(glm::vec3 _position) {
        this->m_Position = _position;
    }

    glm::vec3 FreeflyCamera::getPosition() {
        return this->m_Position;
    }

    glm::vec3 FreeflyCamera::getFuturePosition(float value) {
        return this->m_Position + value * this->moveFrontValue * m_FrontVector;
    }

    glm::mat4 FreeflyCamera::getViewMatrix() const{
        return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
    }

    float FreeflyCamera::getMoveFrontValue() {
        return this->moveFrontValue;
    }

    float FreeflyCamera::getAngleValue() {
        return this->angleValue;
    }

    void FreeflyCamera::updateRotation() {
        int speed = 15;
        if(angleMovingValue < 90 && isTurning){
            angleMovingValue+=speed;
            if(isLeft)
                rotateLeft(speed);
            else
                rotateRight(speed);
        } else {
            angleMovingValue = 0;
            isTurning = false;
        }
    }

    void FreeflyCamera::updateMoving() {
        int speed = 10;
        if(forwardMovingValue < 100 && isMoving){
            forwardMovingValue+=speed;
            if(isForward)
                moveFront(float(speed)/100.);
            else
                moveFront(float(-speed)/100.);
        } else {

            forwardMovingValue = 0;
            isMoving = false;
        }
    }

    void FreeflyCamera::setIsTurning(bool _isTurning) {
        isTurning = _isTurning;
    }

    void FreeflyCamera::setIsForward(bool _isForward) {
        isForward = _isForward;
    }

    void FreeflyCamera::setIsLeft(bool _isLeft) {
        isLeft = _isLeft;
    }

    void FreeflyCamera::setIsMoving(bool _isMoving) {
        isMoving = _isMoving;
    }

    bool FreeflyCamera::getIsTurning() {
        return isTurning;
    }

    bool FreeflyCamera::getIsMoving() {
        return isMoving;
    }

    void FreeflyCamera::resetValues() {
        isTurning = false;
        isMoving  = false;
        isForward = false;
        isLeft    = false;
//        for (int i=0; abs(m_fPhi - M_PI)< EPSILON; ++i){
//        	m_fPhi -= i/180*MPI;
//        }
        //float test = angleMovingValue / 180 * M_PI;
        m_fPhi = M_PI;
        angleValue = 90;
        m_fTheta=0;
        angleMovingValue = 0;
        forwardMovingValue = 0;
    }

}
