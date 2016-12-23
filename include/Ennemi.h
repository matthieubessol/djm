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
#include "Terrain.hpp"

class Ennemi : SceneElement {
	int life;
	Direction direction;

	glm::vec3 getNextPos();
public:
	Ennemi(glm::vec3 pos);
	virtual ~Ennemi();
	void moov(Terrain *t);
};

#endif /* SRC_MONSTER_H_ */
