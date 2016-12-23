/*
 * Porte.h
 *
 *  Created on: 20 déc. 2016
 *      Author: Antoine
 */

#ifndef INCLUDE_DOOR_H_
#define INCLUDE_DOOR_H_
#include "Key.h"
#include "Pixel.hpp"

using namespace glimac;

class Door : SceneElement{
	Key *key;
	Pixel *color;
public:
	Door(glm::vec3 pos,Pixel*p, Key* k=0);
	void setKey(Key *k);
	Pixel* getColor();
	glm::vec3 getPosition(){return SceneElement::getPosition();}
	Key * getKey();
	virtual ~Door();
	//bool operator== (Key* k){return getId() == k->getId();}
};

#endif /* INCLUDE_DOOR_H_ */
