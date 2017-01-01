/*
 * BeginMenu.cpp
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#include "../include/EndMenu.h"
#include "Game.h"

static const std::string START_BTN_TEXT = "floor";

EndMenu::EndMenu() : Menu() {
}

EndMenu::EndMenu(std::string t) : Menu(t){
	restart = new Button(0.2, 0.1, -0.4, -0.3, "floor");
	next = new Button(0.2, 0.1, 0.4, -0.3, "floor");
}

void EndMenu::checkButtons(glm::vec2 cursor, Game* g){
	if(next->isOnButton(cursor.x, cursor.y)){
		g->next();
	}
}
void EndMenu::draw(Game *g){
	g->drawButton(next);
	g->drawButton(restart);
}

EndMenu::~EndMenu() {
	// TODO Auto-generated destructor stub
}
