/*
 * SceneElement.cpp
 *
 *  Created on: 20 déc. 2016
 *      Author: Antoine
 */

#include "SceneElement.h"
static int id_cpt =0;

SceneElement::SceneElement(glm::vec3 pos) {
	// TODO Auto-generated constructor stub
	id = id_cpt++;
	position = pos;
}

int SceneElement::getId(){
	return id;
}

SceneElement::~SceneElement() {
	// TODO Auto-generated destructor stub
}

