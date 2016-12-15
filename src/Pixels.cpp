#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../include/Pixels.hpp"
#include <fstream>

namespace glimac {

Pixels::Pixels() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Pixels::~Pixels() {
}

int Pixels::getRed() {
    return this->r;
}

void Pixels::setRed(int _red) {
    this->r = _red;
}

bool Pixels::isRed() {
    if (this->r == 255)
        return true;
    else
        return false;
}

int Pixels::getGreen() {
    return this->g;
}

void Pixels::setGreen(int _green) {
    this->g = _green;
}

bool Pixels::isGreen() {
    if (this->g == 255)
        return true;
    else
        return false;
}

int Pixels::getBlue() {
    return this->b;
}
void Pixels::setBlue(int _blue) {
    this->b = _blue;
}

bool Pixels::isBlue() {
    if (this->b == 255)
        return true;
    else
        return false;
}

}
