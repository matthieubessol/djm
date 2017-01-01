#pragma once

#include <cstdint>
#include <SDL2/SDL.h>
#include "glm.hpp"

namespace glimac {

class SDLWindowManager {

	uint32_t width, height;
public:
    SDLWindowManager(uint32_t width, uint32_t height, const char* title);

    ~SDLWindowManager();

    bool pollEvent(SDL_Event& e);

    bool isKeyPressed(SDL_Keycode key) const;

    // button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
    bool isMouseButtonPressed(uint32_t button) const;

    glm::vec2 getMousePositionInGL(glm::ivec2 tmp) const;

    glm::ivec2 getMousePosition() const;

    void wrapMousePosition(float x, float y);    

    void swapBuffers();

    // Return the time in seconds
    float getTime() const;

    uint32_t getWidth(){return width;}

    uint32_t getHeight(){return height;}
private:
    SDL_Window * screen;
    SDL_GLContext glcontext;
};

}
