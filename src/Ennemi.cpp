/*
 * Monster.cpp
 *
 *  Created on: 21 déc. 2016
 *      Author: Antoine
 */

#include "Ennemi.h"


Ennemi::Ennemi(glm::vec3 pos) : SceneElement(pos) {
	// TODO Auto-generated constructor stub
	direction = NORTH;
	life = 100;
}

Ennemi::~Ennemi() {
	// TODO Auto-generated destructor stub
}

void Ennemi::moov(Terrain *t){
	if(t->checkCollision(getNextPos())){
		direction = getInverseDirection(direction);
	}
	setPosition(getNextPos());
}

glm::vec3 Ennemi::getNextPos(){
	glm::vec3 nextPos = getDirection(direction);
	return getPosition()+nextPos;
}
