/*
 * Button.h
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

class Button {
	float width,
        height,
        posX,
        posY;
    std::string texture;
public:
	Button(float width, float height, float posX, float posY, std::string texture);
	bool isOnButton(float posx, float posy);
	float getHeight(){return height;}
	float getWidth(){return width;}
	float getPosX(){return posX;}
	float getPosY(){return posY;}
	std::string getTexture(){return texture;}

	virtual ~Button();
};

#endif /* BUTTON_H_ */
