#pragma once

#include <vector>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include "Pixels.hpp"

namespace glimac {

class Pixels {
private:
    int r;
    int g;
    int b;
public:
    Pixels();
    ~Pixels();
    int getRed();
    void setRed(int _red);
    bool isRed();
    int getGreen();
    void setGreen(int _green);
    bool isGreen();
    int getBlue();
    void setBlue(int _blue);
    bool isBlue();
};
}
