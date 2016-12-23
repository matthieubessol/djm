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
	SceneElement();
	SceneElement(SceneElement& e);
	SceneElement(SceneElement* e);
	SceneElement(glm::vec3 pos);
	virtual ~SceneElement();
	int getId() const;
	glm::vec3 getPosition() const;
	bool operator== (SceneElement *e){return getId() == e->getId();}

};

#endif /* INCLUDE_SCENEELEMENT_H_ */
