/*
 * Menu.cpp
 *
 *  Created on: 28 déc. 2016
 *      Author: Antoine
 */

#include "Menu.h"

Menu::Menu(int argc, char* argv[]) {
	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(300, 300);

	main_window = glutCreateWindow("GLUI Example 2");
	glutDisplayFunc(myGlutDisplay);
	glutMouseFunc(myGlutMouse);

	/****************************************/
	/*       Set up OpenGL lights           */
	/****************************************/

	GLfloat light0_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
	GLfloat light0_diffuse[] = { .6f, .6f, 1.0f, 1.0f };
	GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	/****************************************/
	/*          Enable z-buferring          */
	/****************************************/

	glEnable(GL_DEPTH_TEST);

	/****************************************/
	/*         Here's the GLUI code         */
	/****************************************/

	GLUI *glui = GLUI_Master.create_glui("GLUI", 0, 400, 50); /* name, flags,
	 x, and y */
	new GLUI_StaticText(glui, "GLUI Example 2");
	new GLUI_Separator(glui);
	checkbox = new GLUI_Checkbox(glui, "Wireframe", &wireframe, 1, control_cb);
	spinner = new GLUI_Spinner(glui, "Segments:", &segments, 2, control_cb);
	spinner->set_int_limits(3, 60);
	edittext = new GLUI_EditText(glui, "Text:", text, 3, control_cb);
	GLUI_Panel *obj_panel = new GLUI_Panel(glui, "Object Type");
	radio = new GLUI_RadioGroup(obj_panel, &obj, 4, control_cb);
	new GLUI_RadioButton(radio, "Sphere");
	new GLUI_RadioButton(radio, "Torus");
	new GLUI_RadioButton(radio, "Teapot");
	new GLUI_Button(glui, "Quit", 0, (GLUI_Update_CB) exit);

	glui->set_main_gfx_window(main_window);

	/* We register the idle callback with GLUI, *not* with GLUT */
	//GLUI_Master.set_glutIdleFunc( myGlutIdle );
	GLUI_Master.set_glutIdleFunc( NULL);

	glutMainLoop();
}

void Menu::myGlutDisplay(void) {
	glClearColor(.9f, .9f, .9f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode( GL_PROJECTION);
		glLoadIdentity();
		//glFrustum(-xy_aspect * .08, xy_aspect * .08, -.08, .08, .1, 15.0);

		glMatrixMode( GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -1.6f);
		//glRotatef(rotationY, 0.0, 1.0, 0.0);
		//glRotatef(rotationX, 1.0, 0.0, 0.0);

		/*** Now we render object, using the variables 'obj', 'segments', and
		 'wireframe'.  These are _live_ variables, which are transparently
		 updated by GLUI ***/

		if (obj == 0) {
			if (wireframe)
				glutWireSphere(.6, segments, segments);
			else
				glutSolidSphere(.6, segments, segments);
		} else if (obj == 1) {
			if (wireframe)
				glutWireTorus(.2, .5, 16, segments);
			else
				glutSolidTorus(.2, .5, 16, segments);
		} else if (obj == 2) {
			if (wireframe)
				glutWireTeapot(.5);
			else
				glutSolidTeapot(.5);
		}

		glDisable( GL_LIGHTING); /* Disable lighting while we render text */
		glMatrixMode( GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, 100.0, 0.0, 100.0);
		glMatrixMode( GL_MODELVIEW);
		glLoadIdentity();
		glColor3ub(0, 0, 0);
		glRasterPos2i(10, 10);

		//  printf( "text: %s\n", text );

	//	/*** Render the live character array 'text' ***/
	//	for (unsigned int i = 0; i < text.length(); ++i)
	//		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, text[i]);

		glEnable( GL_LIGHTING);

		glutSwapBuffers();
}

void Menu::myGlutMouse(int button, int button_state, int x, int y ){
  if ( button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN ) {
    last_x = x;
    last_y = y;
  }
}


void Menu::control_cb( int control ){
  /********************************************************************
    Here we'll print the user id of the control that generated the
    callback, and we'll also explicitly get the values of each control.
    Note that we really didn't have to explicitly get the values, since
    they are already all contained within the live variables:
    'wireframe',  'segments',  'obj',  and 'text'
    ********************************************************************/

  printf( "callback: %d\n", control );
  printf( "             checkbox: %d\n", checkbox->get_int_val() );
  printf( "              spinner: %d\n", spinner->get_int_val() );
  printf( "          radio group: %d\n", radio->get_int_val() );
  printf( "                 text: %s\n", edittext->get_text() );

}


Menu::~Menu() {

}
