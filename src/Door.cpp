/*
 * Porte.cpp
 *
 *  Created on: 20 déc. 2016
 *      Author: Antoine
 */

#include "Door.h"

Door::Door(glm::vec3 pos, Pixel *p, Key* k) : SceneElement(pos), key(k=NULL), color(p) {
	// TODO Auto-generated constructor stub
}

Door::~Door() {
	// TODO Auto-generated destructor stub
}

void Door::setKey(Key *k){
	key =k;
}

Pixel* Door::getColor(){
	return color;
}

Key * Door::getKey(){
	return key;
}
