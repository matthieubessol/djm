/*
 * Monster.cpp
 *
 *  Created on: 21 déc. 2016
 *      Author: Antoine
 */

#include "Ennemi.h"
#include "Terrain.hpp"

static const float PAS = 50;
static const Direction DIRECTION = NORTH;

Ennemi::Ennemi(glm::vec3 pos) : SceneElement(pos) {
	direction = NORTH;
	validDirection = false;
	life = 100;
}

Ennemi::~Ennemi() {
	// TODO Auto-generated destructor stub
}

void Ennemi::moov(Terrain *t){
	glm::vec3 nextPos = getNextTestPos();
	if(!validDirection){
		while(t->checkCollision(nextPos, this)){
			direction = Ennemi::getNextDirection(direction);
			//std::cout << "change dir : "<< Direction(direction) << std::endl;
			nextPos = getNextTestPos();
		}
		validDirection = true;
	}
	else if(t->checkCollision(nextPos, this)){
		//std::cout<<"next pos : "<<nextPos <<std::endl;
		direction = Ennemi::getInverseDirection(direction);
	}
	nextPos = getNextPos();
	setPosition(nextPos);//operator*(nextPos,0.02)

}

glm::vec3 Ennemi::getNextTestPos(){
	glm::vec3 nextPos = Ennemi::getDirection(direction);
	return getPosition()+nextPos;
}

glm::vec3 Ennemi::getNextPos(){
	glm::vec3 nextPos = Ennemi::getDirection(direction);
	return getPosition()+ (nextPos/PAS);
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
		return glm::vec3(0, 0, 0.5);
	case EAST:
		return glm::vec3(0.5, 0, 0);
	case SOUTH:
		return glm::vec3(0, 0, -0.5);
	case WEST:
		return glm::vec3(-0.5, 0, 0);
	}
}

