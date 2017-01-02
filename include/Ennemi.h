/*
 * Monster.h
 *
 *  Created on: 21 déc. 2016
 *      Author: Antoine
 */

#ifndef SRC_MONSTER_H_
#define SRC_MONSTER_H_

#include "SceneElement.h"
#include "Direction.h"


class Terrain;

class Ennemi : SceneElement {
	int life;
	Direction direction;
	bool validDirection;

	glm::vec3 getNextPos();
	glm::vec3 getNextTestPos();

public:
	Ennemi(glm::vec3 pos);
	virtual ~Ennemi();
	void moov(Terrain *t);
	glm::vec3 getPosition(){return SceneElement::getPosition();}
	static Direction getInverseDirection(Direction d);
	static glm::vec3 getDirection(Direction d);
	Direction getNextDirection(Direction d);
};

#endif /* SRC_MONSTER_H_ */
