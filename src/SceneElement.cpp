/*
 * SceneElement.cpp
 *
 *  Created on: 20 déc. 2016
 *      Author: Antoine
 */

#include "SceneElement.h"
static int id_cpt =0;

SceneElement::SceneElement(){
	id = id_cpt++;
	position = glm::vec3(0, 0, 0);
}

SceneElement::SceneElement(SceneElement& e){
	id = e.id;
	position = e.position;
}

SceneElement::SceneElement(SceneElement* e){
	id = e->id;
	position = e->position;
}


SceneElement::SceneElement(glm::vec3 pos) {
	// TODO Auto-generated constructor stub
	id = id_cpt++;
	position = pos;
}

int SceneElement::getId()const {
	return id;
}

glm::vec3 SceneElement::getPosition()const {
	return position;
}

SceneElement::~SceneElement() {
	// TODO Auto-generated destructor stub
}

void SceneElement::setPosition(glm::vec3 pos){
	position = pos;
}

