/*
 * Button.cpp
 *
 *  Created on: 31 déc. 2016
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
//    x = (x/800.)*2 - 1;
//    y = -(y/600.)*2 + 1;
    std::cout << "click " << x <<" " <<y << std::endl;
	return (x >= posX - width && x <= posX + width
		&& y >= posY -height && y <= posY + height);

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

