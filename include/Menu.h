/*
 * Menu.h
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#ifndef MENU_H_
#define MENU_H_
#include "Button.h"
#include <vector>
#include <glimac/glm.hpp>

class Game;

class Menu {
	//std::vector<Button *> buttons;
protected:
	std::string texture;

public:
	Menu();
	Menu(std::string t);
	virtual ~Menu();
	virtual void checkButtons(glm::vec2 cursor, Game* g)=0;
	virtual void draw(Game *g)=0;
	std::string getTexture(){return texture;}

};

#endif /* MENU_H_ */
