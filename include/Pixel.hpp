#pragma once

#include "Pixel.hpp"

#include <vector>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"

namespace glimac {

class Pixel {
private:
    int r;
    int g;
    int b;
public:
	Pixel(int r, int g, int b);
    ~Pixel();
    int getRed();
    void setRed(int _red);
    bool isRed();
    int getGreen();
    void setGreen(int _green);
    bool isGreen();
    int getBlue();
    void setBlue(int _blue);
    bool isBlue();
    bool isWhite();
};
}
