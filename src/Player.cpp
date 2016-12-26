#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../include/Player.hpp"
#include <glimac/FreeflyCamera.hpp>
#include <glimac/SDLWindowManager.hpp>
#include "Terrain.hpp"


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
	//PlayerItem it;
	if(t->checkCollision(nextPos))
		return;
//	if(it.getPosition() != glm::vec3(0, 0, 0)){
//		addItem(&it);
//		//std::cout<<"Item ajouter ! pos "<<it.getPosition()<<std::endl;
//	}
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

void Player::addItem(PlayerItem *item){
	items.push_back(item);
}

bool Player::hasItem(PlayerItem *item){
	for(unsigned int i=0; i<items.size();++i){
		if(items.at(i) == item)
			return true;
	}
	return false;
}


}
