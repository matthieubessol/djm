/*
 * PlayerItem.h
 *
 *  Created on: 22 déc. 2016
 *      Author: Antoine
 */

#ifndef INCLUDE_PLAYERITEM_H_
#define INCLUDE_PLAYERITEM_H_
#include "SceneElement.h"

class PlayerItem :SceneElement {
public:
	PlayerItem();
	PlayerItem(glm::vec3 pos);
	int getId(){return SceneElement::getId();}
	glm::vec3 getPosition(){return SceneElement::getPosition();}
	virtual ~PlayerItem();
};

#endif /* INCLUDE_PLAYERITEM_H_ */
