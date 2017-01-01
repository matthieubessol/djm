/*
 * BeginMenu.h
 *
 *  Created on: 31 d�c. 2016
 *      Author: Antoine
 */

#ifndef SRC_BEGINMENU_H_
#define SRC_BEGINMENU_H_

#include "Menu.h"

class BeginMenu : public Menu{
	Button *start;
public:
	BeginMenu();
	BeginMenu(std::string t);
	void checkButtons(glm::vec2 cursor, Game* g);
	void draw(Game*g);
	//BeginMenu(std::string t, std::vector<Button*> btns);
	virtual ~BeginMenu();


};

#endif /* SRC_BEGINMENU_H_ */
