#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../include/Player.hpp"
#include <glimac/FreeflyCamera.hpp>
#include <glimac/SDLWindowManager.hpp>


static const int MOOV_FRONT_VALUE = 1;
static const float ROTATE_ANGLE = 90.;

namespace glimac {

	Player::Player() {
		this->health = 100;
		this->camera = new FreeflyCamera();
	}

	Player::~Player() {
	}

	FreeflyCamera* Player::getCamera() {
	  return this->camera;
	}

	int Player::getHealth() {
	  return this->health;
	}

	void Player::setHealth(int _health) {
	  this->health = _health;
	}

	void Player::moovForward(Terrain* t){
		moov(t, MOOV_FRONT_VALUE);
	}

	void Player::moov(Terrain *t, float value){
		glm::vec3 nextPos = camera->getFuturePosition(value);
		if(t->checkCollision(nextPos))
			return;
		camera->moveFront(value);
	}

	void Player::moovBack(Terrain* t){
		moov(t, -MOOV_FRONT_VALUE);
	}

	void Player::lookLeft(){
		camera->rotateLeft(ROTATE_ANGLE);
	}

	void Player::lookRight(){
		camera->rotateRight(ROTATE_ANGLE);
	}

}
