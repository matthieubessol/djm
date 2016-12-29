/*
 * Menu.h
 *
 *  Created on: 28 déc. 2016
 *      Author: Antoine
 */

#ifndef INCLUDE_MENU_H_
#define INCLUDE_MENU_H_
#include <glui/src/include/GL/glui.h>



class Menu {
	GLUI *glui;
	int   main_window;
	int   last_x, last_y;
	/** These are the live variables passed into GLUI ***/
	int   wireframe = 0;
	int   obj = 0;
	int   segments = 8;
	// Using a std::string as a live variable is safe.
	std::string text = "Hello World!";

	// Using a char buffer as a live var is also possible, but it is dangerous
	// because GLUI doesn't know how big your buffer is.
	// But still, it works as long as text doesn't happen to overflow.
	//char  text[200] = {"Hello World!"};

	GLUI_Checkbox   *checkbox;
	GLUI_Spinner    *spinner;
	GLUI_RadioGroup *radio;
	GLUI_EditText   *edittext;

public:
	Menu(int argc, char* argv[]);
	void myGlutDisplay(void);
	void myGlutMouse(int button, int button_state, int x, int y );
	void control_cb( int control );
	virtual ~Menu();
};

#endif /* INCLUDE_MENU_H_ */
