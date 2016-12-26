/*
 * Game.cpp
 *
 *  Created on: 26 déc. 2016
 *      Author: Antoine
 */

#include "Game.h"

const static std::string VS_SHADER_PATH = "/shaders/3D.vs.glsl";
const static std::string FS_SHADER_PATH = "/shaders/multiTex3D.fs.glsl";
const static std::string FLOOR_TEXT_PATH = "/assets/textures/floor.jpg";
const static std::string WALL_TEXT_PATH = "/assets/textures/wall.jpg" ;
const static std::string SKYBOX_TEXT_PATH = "/assets/textures/skybox.jpg";
const static std::string DOOR_TEXT_PATH = "/assets/textures/door.jpg";


Game::Game(std::string dirPath, SDLWindowManager* window) : sphere(1,32,16),
			t(dirPath, &player),
			windowManager(window){
	Program program = loadProgram(dirPath + VS_SHADER_PATH,
								  dirPath + FS_SHADER_PATH);
	program.use();

	/*********************************
	 * HERE SHOULD COME THE INITIALIZATION CODE
	 *********************************/
	// std::vector<std::string> stringTextures;
	// stringTextures.push_back(dirPath + "/assets/textures/EarthMap.jpg");
	// stringTextures.push_back(dirPath + "/assets/textures/MoonMap.jpg");
	textures.insert(std::pair<std::string, Texture *>("floor",new Texture( dirPath + FLOOR_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("wall",new Texture( dirPath + WALL_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("skybox",new Texture( dirPath + SKYBOX_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("door",new Texture( dirPath + DOOR_TEXT_PATH , program.getGLId())));

	//glm::vec3 start = glm::vec3(t.getStartPosition().z, 0, t.getStartPosition().x);
	glm::vec3 start = t.getStartCameraPosition();
	player.getCamera()->setPosition(start);

	uMVPMatrix    = glGetUniformLocation(program.getGLId(),"uMVPMatrix");
	uMVMatrix     = glGetUniformLocation(program.getGLId(),"uMVMatrix");
	uNormalMatrix = glGetUniformLocation(program.getGLId(),"uNormalMatrix");


	ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f) * player.getCamera()->getViewMatrix();
	MVMatrix   = glm::translate(MVMatrix,glm::vec3(0,0,-5)) * player.getCamera()->getViewMatrix();
	NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

	glEnable(GL_DEPTH_TEST);
}


void Game::play(){
	// Application loop:
	bool done = false;
	while(!done) {
		// Event loop:
		SDL_Event e;
		while(windowManager->pollEvent(e)) {
			if(e.type == SDL_KEYDOWN) {
				t.keyEvent(e.key.keysym.sym) ;
				break;
			}
			if(e.type == SDL_QUIT) {
				done = true; // Leave the loop after this iteration
			}
		}

		t.update();

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(cubes.getVao());

		glDisable(GL_TEXTURE_2D);
		glm::mat4 vm = player.getCamera()->getViewMatrix();

		ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f) * vm;
		MVMatrix   = glm::translate(MVMatrix,glm::vec3(0,0,-5)) * vm;

		glm::mat4 MVMatrix;

		cubes.draw(textures.at("skybox"), glm::vec3(t.getWidth()/2,0,t.getHeight()/2), windowManager->getTime(), glm::vec3(1,1,1), glm::vec3(t.getWidth(),t.getWidth(),t.getWidth()));
		glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
		glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
		glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
		glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());

		cubes.draw(textures.at("floor"), glm::vec3(t.getWidth()/2,-0.6,t.getHeight()/2), windowManager->getTime(), glm::vec3(1,1,1), glm::vec3(t.getWidth()/2,0.1,t.getHeight()/2));
		glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
		glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
		glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
		glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());

		glBindVertexArray(0);
		glBindVertexArray(sphere.getVao());
		sphere.draw(textures.at("floor"), glm::vec3(0,0,0), windowManager->getTime(), glm::vec3(0,0,0), glm::vec3(5,5,5));
		glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * sphere.getModelMatrix()));
		glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
		glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
		glDrawArrays(GL_TRIANGLES,0, sphere.getVertexCount());

		int nbCount = 0;
		for(int x = 0; x < t.getWidth(); ++x) {
			for (int y = 0; y < t.getHeight(); ++y){
				if(t.isWall(glm::vec3(x, 0, y))) {
					glBindVertexArray(0);
					glBindVertexArray(cubes.getVao());
					cubes.draw(textures.at("wall"), x, y);
					glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
					glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
					glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
					glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());
				}
				else if(t.isDoor(glm::vec3(x, 0, y))){
					glBindVertexArray(0);
					glBindVertexArray(cubes.getVao());
					cubes.draw(textures.at("door"), x, y);
					glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
					glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
					glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
					glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());
				}
				else if(t.isKey(glm::vec3(x, 0, y))){
					glBindVertexArray(0);
					glBindVertexArray(sphere.getVao());
					sphere.draw(textures.at("floor"), x, y);
					glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * sphere.getModelMatrix()));
					glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
					glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
					glDrawArrays(GL_TRIANGLES,0, sphere.getVertexCount());
				}
				else if(t.isEnnemi(glm::vec3(x, 0, y))){
					glBindVertexArray(0);
					glBindVertexArray(sphere.getVao());
					sphere.draw(textures.at("floor"), x, y);
					glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * sphere.getModelMatrix()));
					glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
					glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
					glDrawArrays(GL_TRIANGLES,0, sphere.getVertexCount());
				}
				nbCount++;
			}
		}
		glBindVertexArray(0);
		windowManager->swapBuffers();
	}
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

