/*
 * Bonus.h
 *
 *  Created on: 16 déc. 2016
 *      Author: luxkyluke
 */

#ifndef INCLUDE_BONUS_H_
#define INCLUDE_BONUS_H_

#include "SceneElement.h"

class Bonus : public SceneElement {
private:

public:
	Bonus();
	glm::vec3 getPosition(){return SceneElement::getPosition();}
	virtual ~Bonus();
};

#endif /* INCLUDE_BONUS_H_ */
