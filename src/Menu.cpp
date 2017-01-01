/*
 * Menu.cpp
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#include "Menu.h"
#include "Game.h"


Menu::Menu(){
}

Menu::Menu(std::string t) {
	texture = t;
}

//Menu::Menu(std::string t, std::vector<Button*> btns){
//	texture = t;
//	//buttons = btns;
//}
//
//void Menu::addButton(Button *b){
//	buttons.push_back(b);
//}

//bool Menu::checkButtons(glm::vec2 cursor){
//	for(unsigned int i=0 ;i<buttons.size(); ++i){
//		if(buttons.at(i)->isOnButton(cursor.x, cursor.y)){
//			return false;
//		}
//	}
//	return true;
//}


Menu::~Menu() {
}


