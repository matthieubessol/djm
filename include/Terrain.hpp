#pragma once

#include <vector>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include "Pixel.hpp"
#include "Bonus.h"
#include "Door.h"
#include "Key.h"

namespace glimac{
// Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Terrain {
private:
	std::string path;
	int width;
	int height;
	std::vector<std::vector<Pixel*>*> pixels;
	std::vector<Door*> doors;
	std::vector<Key*> keys;
	glm::vec2 startPosition;
	glm::vec2 finishPosition;
	std::vector<Bonus*> bonus;
	// std::vector< std::vector<int> > matriceMap;

public:
	// Constructeur: alloue le tableau de données et construit les attributs des vertex
	//Terrain();
	Terrain(std::string _path);
	~Terrain();
	int getWidth();
	int getHeight();
	void loadMap();
	glm::vec3 getStartCameraPosition();
	bool isWall(glm::vec3 pos);
	Key* findKey(Pixel* door);
	Key* findKey(Door* door);
	bool checkCollision(glm::vec3 playerPosition);
	bool checkReachEnd(glm::vec3 playerPosition);
	bool isInTerrain(glm::vec3 playerPosition);
	bool isInTerrain(glm::vec2 playerPosition);
	void checkPixelSignification(Pixel* p, int x, int y);
	Pixel* getPixel(glm::vec2& pos);
	glm::vec2 get2DIntPosition(glm::vec3& pos);
	void linkDoors();

};
}
