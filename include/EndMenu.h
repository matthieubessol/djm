/*
 * BeginMenu.h
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#ifndef SRC_ENDMENU_H_
#define SRC_ENDMENU_H_

#include "Menu.h"

class EndMenu : public Menu{
	Button *restart, *quit, *next;
public:
	EndMenu();
	EndMenu(std::string t);
	void checkButtons(glm::vec2 cursor, Game* g);
	void draw(Game*g);
	//BeginMenu(std::string t, std::vector<Button*> btns);
	virtual ~EndMenu();

};

#endif /* SRC_ENDMENU_H_ */
