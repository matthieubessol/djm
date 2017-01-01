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
    x = (x/800.)*2 - 1;
    y = -(y/600.)*2 + 1;
    std::cout << "click " << x <<" " <<y << std::endl;
	return (x >= posX - width/2 && x <= posX + width/2
		&& y >= posY -height/2 && y <= posY + height/2);

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

