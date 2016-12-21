/*
 * Key.h
 *
 *  Created on: 20 déc. 2016
 *      Author: Antoine
 */

#ifndef INCLUDE_KEY_H_
#define INCLUDE_KEY_H_
#include "SceneElement.h"
#include "Pixel.hpp"

using namespace glimac;

class Key : SceneElement{

	Pixel *color;
public:
	Key(glm::vec3 pos, Pixel *p);
	Pixel* getColor();
	int getId(){return SceneElement::getId();}
	glm::vec3 getPosition(){return SceneElement::getPosition();}
	virtual ~Key();

};

#endif /* INCLUDE_KEY_H_ */
