/*
 * BeginMenu.h
 *
 *  Created on: 31 déc. 2016
 *      Author: Antoine
 */

#ifndef SRC_BEGINMENU_H_
#define SRC_BEGINMENU_H_

#include "Menu.h"

class BeginMenu : public Menu{
public:
	BeginMenu();
	BeginMenu(std::string t);
	BeginMenu(std::string t, std::vector<Button*> btns);
	virtual ~BeginMenu();
};

#endif /* SRC_BEGINMENU_H_ */
