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


Game::Game(std::string dirPath, SDLWindowManager* window) : sphere(1,32,16), windowManager(window){
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
	textures.insert(std::pair<std::string, Texture *>("key",new Texture( dirPath + DOOR_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("bonus",new Texture( dirPath + DOOR_TEXT_PATH , program.getGLId())));


	//glm::vec3 start = glm::vec3(t.getStartPosition().z, 0, t.getStartPosition().x);

	t = Terrain(dirPath, &player);
	glm::vec3 start = t.getStartPosition();
	player = Player(start);

	uMVPMatrix    = glGetUniformLocation(program.getGLId(),"uMVPMatrix");
	uMVMatrix     = glGetUniformLocation(program.getGLId(),"uMVMatrix");
	uNormalMatrix = glGetUniformLocation(program.getGLId(),"uNormalMatrix");
	uKd 	  	  = glGetUniformLocation(program.getGLId(),"uKd");
	uKs 	  	  = glGetUniformLocation(program.getGLId(),"uKs");
	uLightDir_vs    = glGetUniformLocation(program.getGLId(),"uLightDir_vs");
	uLightIntensity = glGetUniformLocation(program.getGLId(),"uLightIntensity");


	ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f) * player.getViewMatrix();
	MVMatrix   = glm::translate(MVMatrix,glm::vec3(0,0,-5)) * player.getViewMatrix();
	NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

	glEnable(GL_DEPTH_TEST);
}

//void test(){
//	glBindVertexArray(cubes.getVao());
//		cubes.draw(textures.at("wall"), 9, 17);
//		glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
//		glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
//		glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
//		glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());
//	glBindVertexArray(0);
//}

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
		glm::mat4 vm = player.getViewMatrix();

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
		glBindVertexArray(0);

		t.draw(this);

		windowManager->swapBuffers();
	}
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}


void Game::drawSphere(std::string texture, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale){
	glm::mat4 MVMatrix;

	Texture *text = textures.at(texture);
	if(!text)
		return;

	glBindVertexArray(sphere.getVao());
	sphere.draw(text, translate, windowManager->getTime(), rotate, scale);
	glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * sphere.getModelMatrix()));
	glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
	glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

	glm::vec3 kd = glm::vec3(0.7,0.7,0.7);

	glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0.7,0.7,0.7)));
	glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0.7,0.7,0.7)));
	glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(01,01,01)));
	glUniform3fv(uLightDir_vs, 1, glm::value_ptr(glm::vec3(1,1,1)));

	glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
	glBindVertexArray(0);
	//std::cout<<"draw sphere pos"<<translate<<std::endl;
}

void Game::drawCube(std::string texture, glm::vec3 translate, glm::vec3 rotate, glm::vec3 scale){
	glm::mat4 MVMatrix;

	Texture *text = textures.at(texture);
	if(!text)
		return;

	glBindVertexArray(cubes.getVao());
	cubes.draw(text, translate, windowManager->getTime(), rotate, scale);
	glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
	glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
	glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

	glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0.7,0.7,0.7)));
	glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0.7,0.7,0.7)));
	glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(0.4,0.4,0.4)));
	glUniform3fv(uLightDir_vs, 1, glm::value_ptr(glm::vec3(1,1,1)));

	glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());
	glBindVertexArray(0);
	//std::cout<<"draw cube pos"<<translate<<std::endl;
}

