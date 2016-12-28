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

//namespace glimac {
Player::Player(){
	this->health = 0;
	this->camera = NULL;
}


Player::Player(glm::vec3 pos) : SceneElement(pos) {
	this->health = 100;
	this->camera = new FreeflyCamera();
	camera->setPosition(pos);
}

Player::~Player() {
}

void Player::moovForward(Terrain* t){
	moov(t, MOOV_FRONT_VALUE);
}

void Player::moov(Terrain *t, float value){
	glm::vec3 nextPos = camera->getFuturePosition(value);
	if(t->checkCollision(nextPos, this))
		return;

	camera->moveFront(value);
	setPosition(camera->getPosition());
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

void Player::kill(){
	health = 0;
}

glm::mat4 Player::getViewMatrix(){
	return camera->getViewMatrix();
}

glm::vec3 Player::getFrontVector() {
	return camera->getFrontVector();
}

//}
