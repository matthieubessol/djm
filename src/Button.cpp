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
    x = x/800. - 0.5;
    y = y/600. - 0.5;
	return (x >= posX - width/2 && x <= posX + width/2
		&& y >= posY -height/2 && y <= posY + height/2);

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

