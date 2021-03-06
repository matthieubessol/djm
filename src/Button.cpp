/*
 * Button.cpp
 *
 *  Created on: 31 d�c. 2016
 *      Author: Antoine
 */

#include "Button.h"
#include <iostream>

Button::Button(float w, float h, float x, float y, std::string t) {
	width =w;
	height =h;
	posX = x;
	posY = y;
	texture = t;
}

bool Button::isOnButton(float x, float y){
	return (x >= posX - width && x <= posX + width
		&& y >= posY -height && y <= posY + height);

}

Button::~Button() {
}

