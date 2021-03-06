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
static const int NB_LIFE = 3;

Player::Player(){
	this->nbLife = NB_LIFE;
	this->camera = new FreeflyCamera();
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
	if(!camera->getIsTurning() && !camera->getIsMoving()) {
		moov(t, MOOV_FRONT_VALUE);
	}
}

void Player::moov(Terrain *t, float value){
	glm::vec3 nextPos = camera->getFuturePosition(value);
	if(t->checkCollision(nextPos, this))
		return;

	if(value>0)
		camera->setIsForward(true);
	else
		camera->setIsForward(false);
	camera->setIsMoving(true);
	setPosition(camera->getPosition());
}

void Player::moovBack(Terrain* t){
	if(!camera->getIsTurning() && !camera->getIsMoving()) {
		moov(t, -MOOV_FRONT_VALUE);
	}
}

void Player::lookLeft(){
	if(!camera->getIsTurning() && !camera->getIsMoving()) {
		camera->setIsTurning(true);
		camera->setIsLeft(true);
	}
}

void Player::lookRight(){
	if(!camera->getIsTurning() && !camera->getIsMoving()) {
		camera->setIsTurning(true);
		camera->setIsLeft(false);
	}
}

void Player::addItem(PlayerItem *item){
	items.push_back(item);
}


bool Player::findAndRemove(PlayerItem *item){
	for(unsigned int i=0; i<items.size();++i){
		if(items.at(i) == item){
			items.erase(items.begin()+i);
			Key *test = dynamic_cast<Key*>(item);
			return true;
		}
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

int Player::getNbKey(){
	return items.size();
}

void Player::kill(){
	if(clock() - timer > REANIMATION_DURATION){
		--nbLife;
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
	camera->updateMoving();
	setPosition(camera->getPosition());

}

int Player::getLife() {
	return nbLife;
}

bool Player::isDead(){
	return nbLife<=0;
}

void Player::setPosition(glm::vec3 pos){
	camera->setPosition(pos);
	SceneElement::setPosition(pos);
}

void Player::reset(){
	for (std::vector<PlayerItem*>::iterator it = items.begin() ; it != items.end(); ++it){
		delete (*it);
	}
	items.clear();
	nbLife = NB_LIFE;
	camera->resetValues();
}
