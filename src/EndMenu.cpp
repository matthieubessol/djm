/*
 * BeginMenu.cpp
 *
 *  Created on: 31 d�c. 2016
 *      Author: Antoine
 */

#include "../include/EndMenu.h"
#include "Game.h"

static const std::string START_BTN_TEXT = "floor";

EndMenu::EndMenu() : Menu() {
}

EndMenu::EndMenu(std::string t) : Menu(t){
	restart = new Button(0.2, 0.1, -0.4, -0.3, "restart");
	next = new Button(0.2, 0.1, 0.4, -0.3, "continuer");
}

void EndMenu::checkButtons(glm::vec2 cursor, Game* g){
	if(next->isOnButton(cursor.x, cursor.y)){
		g->next();
	}
	else if(restart->isOnButton(cursor.x, cursor.y)){
		g->restart();
	}
}

void EndMenu::draw(Game *g){
	g->drawButton(next);
	g->drawButton(restart);
}

EndMenu::~EndMenu() {
	// TODO Auto-generated destructor stub
}
