#pragma once

#include <vector>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include <glimac/SDLWindowManager.hpp>
#include "Pixel.hpp"
#include "Bonus.h"
#include "Door.h"
#include "Key.h"
#include "Ennemi.h"
//#include "Player.hpp"

class Game;

//namespace glimac{
class Player;


// Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class Terrain {
private:
	std::string path;
	int width;
	int height;
	std::vector<std::vector<Pixel*>*> pixels;
	std::vector<Door*> doors;
	std::vector<SceneElement*> walls;
	std::vector<Key*> keys;
	glm::vec2 startPosition;
	glm::vec2 finishPosition;
	std::vector<Bonus*> bonus;
	Player* player;
	std::vector<Ennemi*> ennemis;


	void drawKeys(Game *g);
	void drawBonus(Game *g);
	void drawDoors(Game *g);
	void drawWalls(Game *g);
	void drawEnnemis(Game *g);
	void drawInterface(Game *g);

public:
	// Constructeur: alloue le tableau de données et construit les attributs des vertex
	//Terrain();
	Terrain();
	Terrain(std::string _path, Player* p);
	~Terrain();
	int getWidth();
	int getHeight();
	void loadMap();
	glm::vec3 getStartPosition();
	bool isWall(glm::vec3 pos);
	bool isDoor(glm::vec3 pos);
	bool isKey(glm::vec3 pos);
	//Key* findKey(glm::vec3 pos);
	Key* findKey(Pixel* door);
	Key* findKey(Door* door);
	bool checkCollision(glm::vec3 playerPosition, SceneElement *e);
	bool checkReachEnd(glm::vec3 playerPosition);
	bool isInTerrain(glm::vec3 playerPosition);
	bool isInTerrain(glm::vec2 playerPosition);
	void checkPixelSignification(Pixel* p, int x, int y);
	Pixel* getPixel(glm::vec2& pos);
	Pixel* getPixel(glm::vec3& p);
	static glm::vec2 get2DIntPosition(glm::vec3& pos);
	static bool isInTheSameCase(glm::vec3& pos1, glm::vec3& pos2);
	void linkDoors();
	Key* getKey(glm::vec3 pos);
	Door* getDoor(glm::vec3 pos);
	void removeKey(Key* k);
	void removeDoor(Door* k);
	Key* recoverKey(glm::vec3 pos);
	bool keyEvent(int  key);
	bool isEnnemi(glm::vec3 pos);
	bool isPlayer(glm::vec3 pos);
	void update();
	void draw(Game *g);
};
//}
