/*
 * Button.cpp
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#include "Button.h"

Button::Button(float w, float h, float x, float y, std::string t) {
	width =w;
	height =h;
	posX = x;
	posY = y;
	texture = t;
}

bool Button::isOnButton(float x, float y){
	return (x >= posX && x <= posX + width
				&& y >= posY && y <= posY + height);

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

