#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../include/Player.hpp"

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

}
