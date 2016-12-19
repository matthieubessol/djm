#include <Pixel.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include <fstream>

namespace glimac {

    Pixel::Pixel(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    Pixel::~Pixel() {
    }

    int Pixel::getRed() {
        return this->r;
    }

    // void Pixel::setRed(int _red) {
    //     this->r = _red;
    // }

    bool Pixel::isRed() {
        return (r == 255 && g == 0 && b==0);
    }

    int Pixel::getGreen() {
        return this->g;
    }

    // void Pixel::setGreen(int _green) {
    //     this->g = _green;
    // }

    bool Pixel::isGreen() {
        if (this->g == 255 && r == 0 && b==0)
            return true;
        else
            return false;
    }

    int Pixel::getBlue() {
        return this->b;
    }
    // void Pixel::setBlue(int _blue) {
    //     this->b = _blue;
    // }

    bool Pixel::isBlue() {
        if (this->b == 255 && g==0 && r==0)
            return true;
        else
            return false;
    }

    bool Pixel::isWhite() {
        if(this->b == 255 && this->r == 255 && this->g == 255)
            return true;
        else
            return false;
    }

    bool Pixel::operator==(const Pixel& p){
        return (r==p.r && g==p.g && b==p.b);
    }
}
