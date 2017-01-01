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
	addButton(new Button(0.2, 0.1, 0, 0, "start"));
}

BeginMenu::BeginMenu(std::string t, std::vector<Button*> btns) : Menu(t, btns){
	addButton(new Button(0.2, 0.1, 0, 0, "start"));
}

BeginMenu::~BeginMenu() {
	// TODO Auto-generated destructor stub
}

