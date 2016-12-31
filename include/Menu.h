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

class Game;

class Menu {
	std::vector<Button *> buttons;
	std::string texture;

public:
	Menu();
	Menu(std::string t);
	Menu(std::string t, std::vector<Button*> btns);
	void addButton(Button *b);
	std::vector<Button*> getButtons(){return buttons;}
	virtual ~Menu();
	std::string getTexture(){return texture;}
};

#endif /* MENU_H_ */
