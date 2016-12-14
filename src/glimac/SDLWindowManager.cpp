#include "glimac/SDLWindowManager.hpp"
#include <iostream>

namespace glimac {

SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title) {
    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

    //antialiasing
    if (SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) == -1)
        std::cerr << "impossible d'initialiser SDL_GL_MULTISAMPLEBUFFERS à 1" ;
    else{
        if (SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 6 ) == -1)
            std::cerr << "impossible d'initialiser SDL_GL_MULTISAMPLESAMPLES sur 6 buffers";
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    screen = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!screen) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }
    glcontext = SDL_GL_CreateContext(screen);
    std::cerr << SDL_GetError() << std::endl;
    SDL_ShowCursor(0);
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    /*
    SDL_ShowCursor(0);
    SDL_WM_GrabInput(SDL_GRAB_ON);
    */
}

SDLWindowManager::~SDLWindowManager() {
    SDL_DestroyWindow(screen);
    SDL_GL_DeleteContext(glcontext);
    SDL_Quit();
}

bool SDLWindowManager::pollEvent(SDL_Event& e) {
    return SDL_PollEvent(&e);
}

bool SDLWindowManager::isKeyPressed(SDL_Keycode key) const {
    return SDL_GetKeyboardState(nullptr)[SDL_GetScancodeFromKey(key)];
}

// button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

glm::ivec2 SDLWindowManager::getMousePosition() const {
    glm::ivec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    return mousePos;
}

void SDLWindowManager::wrapMousePosition(float x, float y) {
  SDL_WarpMouseInWindow(screen, x, y);
  //SDL_WarpMouse();
}

void SDLWindowManager::swapBuffers() {
    SDL_GL_SwapWindow(screen);
}

float SDLWindowManager::getTime() const {
    return 0.001f * SDL_GetTicks();
}

}
