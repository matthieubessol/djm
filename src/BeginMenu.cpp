/*
 * BeginMenu.cpp
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#include <BeginMenu.h>
#include "Game.h"

static const std::string START_BTN_TEXT = "start";

BeginMenu::BeginMenu() : Menu() {
}

BeginMenu::BeginMenu(std::string t) : Menu(t){
	start = new Button(0.2, 0.1, 0, -0.3, START_BTN_TEXT);
}

void BeginMenu::checkButtons(glm::vec2 cursor, Game* g){
	if(start->isOnButton(cursor.x, cursor.y)){
		g->start();
	}
}
void BeginMenu::draw(Game *g){
	g->drawButton(start);
}


BeginMenu::~BeginMenu() {
	// TODO Auto-generated destructor stub
}
