/*
 * SceneElement.h
 *
 *  Created on: 20 déc. 2016
 *      Author: Antoine
 */

#ifndef INCLUDE_SCENEELEMENT_H_
#define INCLUDE_SCENEELEMENT_H_
#include "glimac/glm.hpp"

class SceneElement {
	int id;
	glm::vec3 position;
public:
	SceneElement(glm::vec3 pos);
	virtual ~SceneElement();
	int getId();

};

#endif /* INCLUDE_SCENEELEMENT_H_ */
