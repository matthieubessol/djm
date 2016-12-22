/*
 * Key.cpp
 *
 *  Created on: 20 déc. 2016
 *      Author: Antoine
 */

#include "Key.h"

Key::Key():PlayerItem(){
}

Key::Key(glm::vec3 pos, Pixel *p): PlayerItem(pos), color(p){
	// TODO Auto-generated constructor stub

}

Key::~Key() {
	// TODO Auto-generated destructor stub
}

Pixel* Key::getColor(){
	return color;
}
