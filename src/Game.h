/*
 * Game.h
 *
 *  Created on: 26 déc. 2016
 *      Author: Antoine
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <iostream>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <vector>
#include <map>
#include "Cube.hpp"
#include "Player.hpp"
#include "Terrain.hpp"

using namespace glimac;

class Game {
	SDLWindowManager *windowManager;
	std::map<std::string, Texture *> textures;
	Terrain t;
	Cube cubes;
	Sphere sphere;
	Player player;
	GLint uMVPMatrix;
	GLint uMVMatrix;
	GLint uNormalMatrix;
	glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;

public:
	Game(std::string dirPath, SDLWindowManager* window);
	void play();
	virtual ~Game();
};

#endif /* SRC_GAME_H_ */
