/*
 * BeginMenu.cpp
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#include "BeginMenu.h"

BeginMenu::BeginMenu() : Menu() {
	// TODO Auto-generated constructor stub

}

BeginMenu::BeginMenu(std::string t) : Menu(t){
	addButton(new Button(200, 100, 0, 0, "floor"));
}

BeginMenu::BeginMenu(std::string t, std::vector<Button*> btns) : Menu(t, btns){
	addButton(new Button(200, 100, 0, 0, "floor"));
}

BeginMenu::~BeginMenu() {
	// TODO Auto-generated destructor stub
}

