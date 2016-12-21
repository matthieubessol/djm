/*
 * Monster.h
 *
 *  Created on: 21 d�c. 2016
 *      Author: Antoine
 */

#ifndef SRC_MONSTER_H_
#define SRC_MONSTER_H_

#include "SceneElement.h"

class Monster : SceneElement {
	int life;
	int xp;
public:
	Monster(glm::vec3 pos);
	virtual ~Monster();
};

#endif /* SRC_MONSTER_H_ */
