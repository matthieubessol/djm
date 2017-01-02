/*
 * Key.h
 *
 *  Created on: 20 déc. 2016
 *      Author: Antoine
 */

#ifndef INCLUDE_KEY_H_
#define INCLUDE_KEY_H_
#include "PlayerItem.h"
#include "Pixel.hpp"

using namespace glimac;

class Key : public PlayerItem{

	Pixel *color;
public:
	Key();
	Key(glm::vec3 pos, Pixel *p);
	Pixel* getColor();
	int getId(){return PlayerItem::getId();}
	glm::vec3 getPosition(){return PlayerItem::getPosition();}
	virtual ~Key();

};

#endif /* INCLUDE_KEY_H_ */
