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
#include "json.hpp"

using Json = nlohmann::json;

class Game;

class Player;


class Terrain {
private:
	std::string imgPath;
	int width;
	int height;

	std::vector<std::vector<Pixel*>*> pixels;
	std::vector<Door*> doors;
	std::vector<SceneElement*> walls;
	std::vector<SceneElement*> tresors;
	std::vector<SceneElement*> lifes;
	std::vector<Key*> keys;
	std::vector<Ennemi*> ennemis;
	std::vector<std::string> maps;

	glm::vec3 startPosition;
	glm::vec3 finishPosition;
	Player* player;
	Json json;
	bool thisIsTheEnd;
	int indMap;


	void drawKeys(Game *g);
	void drawBonus(Game *g);
	void drawDoors(Game *g);
	void drawWalls(Game *g);
	void drawEnnemis(Game *g);
	void drawLife(Game *g);
	void drawInterface(Game *g);
	void drawTresors(Game *g);
	void init();
	void loadMap(std::string map);
	void reset();
	void drawFloor(Game *g);
	void drawSkyBox(Game *g);
	int recoveryTresor(glm::vec3 pos);
	bool recoveryLife(glm::vec3 pos);

public:
	//Terrain();
	Terrain();
	Terrain(std::string _path, Player* p, std::string filePath);
	~Terrain();
	int getWidth();
	int getHeight();

	glm::vec3 getStartPosition();
	bool isWall(glm::vec3 pos);
	bool isDoor(glm::vec3 pos);
	bool isKey(glm::vec3 pos);
	bool isEnd(glm::vec3 pos);
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
	bool update();
	void draw(Game *g);

	void drawMinimap(Game *g);
	std::string getPixelSignificationString(Pixel* p);
	void next();
	void restart();
};
