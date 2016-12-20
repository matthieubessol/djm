#pragma once

#include "Pixel.hpp"

#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>

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
	bool isRed();
	int getGreen();
	bool isGreen();
	int getBlue();
	bool isBlue();
	bool isWhite();
	bool isWall();
	bool operator==(const Pixel& p);
	bool isKey();
	bool isDoor();
	bool isEnd();
	bool isStart();
	bool isMyKey(Pixel *p);
	bool isMyDoor(Pixel* door);
	std::ostream& operator<<(Pixel& p);
};

}
