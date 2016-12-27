#include <Pixel.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include <fstream>

namespace glimac{
static const Pixel BONUS_LIFE = Pixel(100, 100, 100); //#646464
static const Pixel BONUS_POWER = Pixel(150, 150, 150); //#969696
static const Pixel WALL_COLOR = Pixel(255, 0, 0);
static const Pixel ENNEMI_COLOR = Pixel(0, 0, 0);
static const Pixel START_COLOR = Pixel(255, 0, 255);


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

bool Pixel::isRed() {
	return (r == 255 && g == 0 && b==0);
}

int Pixel::getGreen() {
	return this->g;
}

bool Pixel::isGreen() {
	if (this->g == 255 && r == 0 && b==0)
		return true;
	else
		return false;
}

int Pixel::getBlue() {
	return this->b;
}

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

//key = [0, 0, 150] => [0, 0, 254]
bool Pixel::isKey(){
	return (r==0 && g==0 && b>149 && b<255);
}

//door = [0, 150, 0] => [0, 254, 0]
bool Pixel::isDoor(){
	return (r==0 && b==0 && g>149 && g<255);
}

bool Pixel::isWall(){
	return (*this == WALL_COLOR);
}

bool Pixel::isEnd(){
	return this->isGreen();
}

bool Pixel::isStart(){
	return (*this == START_COLOR);
}

bool Pixel::isMyKey(Pixel* key){
	if(!this->isDoor() || !key->isKey())
		return false;
	if(g==key->b)
		return true;
	return false;
}

bool Pixel::isMyDoor(Pixel* door){
	return door->isMyKey(this);
}

bool Pixel::isEnnemi(){
	return (*this == ENNEMI_COLOR);
}

std::ostream& Pixel::operator<<(Pixel& p){
	return std::cout<<"r : "<<r<<" g : "<<g<<" b: "<<b<<std::endl;
}



}
