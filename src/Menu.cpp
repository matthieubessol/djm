/*
 * Menu.cpp
 *
 *  Created on: 31 d�c. 2016
 *      Author: Antoine
 */

#include "Menu.h"
#include "Game.h"

Menu::Menu(){
}

Menu::Menu(std::string t) {
	texture = t;
}

Menu::Menu(std::string t, std::vector<Button*> btns){
	texture = t;
	buttons = btns;
}

void Menu::addButton(Button *b){
	buttons.push_back(b);
}

Menu::~Menu() {
}


