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
static const int REANIMATION_DURATION = 2000;

Player::Player(){
	this->nbLife = 0;
	this->camera = NULL;
	timer = 0;
	money =0;
}


Player::Player(glm::vec3 pos) : SceneElement(pos) {
	this->nbLife = 3;
	this->camera = new FreeflyCamera();
	camera->setPosition(pos);
	timer=0;
	money =0;
}

Player::~Player() {
}

void Player::moovForward(Terrain* t){
	if(!camera->getIsTurning())
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
	if(!camera->getIsTurning())
		moov(t, -MOOV_FRONT_VALUE);
}

void Player::lookLeft(){
	camera->setIsTurning(true);
	camera->setIsLeft(true);
}

void Player::lookRight(){
	camera->setIsTurning(true);
	camera->setIsLeft(false);
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

void Player::addMoney(int value){
	if(value<0)
		return;
	money += value;
}

int Player::getMoney(){
	return money;
}

int Player::getNbLife(){
	return nbLife;
}

void Player::kill(){
	if(clock() - timer > REANIMATION_DURATION){
		if(--nbLife < 1){
			std::cout<<"fin du game"<<std::endl;
		}
		std::cout<<"KILL !!! vie restante = "<< nbLife<<std::endl;
		timer = clock();
	}
}

glm::vec3 Player::getNextFrontPosition(){
	return camera->getFuturePosition(MOOV_FRONT_VALUE);
}

glm::mat4 Player::getViewMatrix(){
	return camera->getViewMatrix();
}

glm::vec3 Player::getFrontVector() {
	return camera->getFrontVector();
}

void Player::moveUpdate(){
	camera->updateRotation();
}

int Player::getLife() {
	return nbLife;
}
