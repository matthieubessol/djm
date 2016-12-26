
#include "Game.h"

using namespace glimac;

int main(int argc, char** argv) {
	// Initialize SDL and open a window
	SDLWindowManager windowManager(800, 600, "GLImac");
	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	// Initialize SDL and open a window

	FilePath applicationPath(argv[0]);
	std::cout<<"direpath : "<<applicationPath.dirPath()<<std::endl;

    Game game(applicationPath.dirPath().str(), &windowManager);
    game.play();

    return EXIT_SUCCESS;
}
