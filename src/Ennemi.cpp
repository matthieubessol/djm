/*
 * Monster.cpp
 *
 *  Created on: 21 déc. 2016
 *      Author: Antoine
 */

#include "Ennemi.h"
#include "Terrain.hpp"

static const float PAS = 0.01;

Ennemi::Ennemi(glm::vec3 pos) : SceneElement(pos) {
	// TODO Auto-generated constructor stub
	direction = EAST;
	life = 100;
}

Ennemi::~Ennemi() {
	// TODO Auto-generated destructor stub
}

void Ennemi::moov(Terrain *t){
	glm::vec3 nextPos = getNextPos();
	if(t->checkCollision(nextPos)){
		direction = Ennemi::getInverseDirection(direction);
	}
	//std::cout<<"ennemi pos "<<nextPos<<std::endl;
	setPosition(nextPos);

}

glm::vec3 Ennemi::getNextPos(){
	glm::vec3 nextPos = Ennemi::getDirection(direction);
	return getPosition()+nextPos;
}

Direction Ennemi::getInverseDirection(Direction d){
	switch(d){
	case NORTH:
		return SOUTH;
	case EAST:
		return WEST;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	}
}

Direction Ennemi::getNextDirection(Direction d){
	switch(d){
	case NORTH:
		return EAST;
	case EAST:
		return SOUTH;
	case SOUTH:
		return WEST;
	case WEST:
		return NORTH;
	}
}

glm::vec3 Ennemi::getDirection(Direction d){
	switch(d){
	case NORTH:
		return glm::vec3(0, 0, PAS);
	case EAST:
		return glm::vec3(PAS, 0, 0);
	case SOUTH:
		return glm::vec3(0, 0, -PAS);
	case WEST:
		return glm::vec3(-PAS, 0, 0);
	}
}

