/*
 * Game.cpp
 *
 *  Created on: 26 d�c. 2016
 *      Author: Antoine
 */

#include "Game.h"
#include "Button.h"
#include <SDL/SDL.h>
const static std::string VS_SHADER_PATH = "/shaders/3D.vs.glsl";
const static std::string FS_SHADER_PATH = "/shaders/multiTex3D.fs.glsl";
const static std::string FLOOR_TEXT_PATH = "/assets/textures/floor.jpg";
const static std::string WALL_TEXT_PATH = "/assets/textures/wall.jpg" ;
const static std::string SKYBOX_TEXT_PATH = "/assets/textures/skybox.jpg";
const static std::string DOOR_TEXT_PATH = "/assets/textures/door.jpg";
const static std::string HEART_TEXT_PATH = "/assets/textures/heart.png";
const static std::string TRESOR_TEXT_PATH = "/assets/textures/coin.png";
const static std::string GRIS_TEXT_PATH = "/assets/textures/gris.jpg";
const static std::string BLUE_TEXT_PATH = "/assets/textures/blue.jpg";
const static std::string LIGHTBLUE_TEXT_PATH = "/assets/textures/light-blue.jpg";
const static std::string YELLOW_TEXT_PATH = "/assets/textures/jaune.jpg";
const static std::string BLACK_TEXT_PATH = "/assets/textures/black.jpg";
const static std::string RED_TEXT_PATH = "/assets/textures/rouge.jpg";
const static std::string GREEN_TEXT_PATH = "/assets/textures/green.jpg";
const static std::string WHITE_TEXT_PATH = "/assets/textures/white.jpg";
const static std::string BEGIN_MENU_TEXT_PATH = "/assets/textures/menu_deb.png";
const static std::string CURSOR_TEXT_PATH = "/assets/textures/cursor.png";
const static std::string FIRE_TEXT_PATH = "/assets/textures/fire.png";
const static std::string KEY_TEXT_PATH = "/assets/textures/key.jpg";
const static std::string MINI_KEY_TEXT_PATH = "/assets/textures/mini_key.png";
const static std::string START_TEXT_PATH = "/assets/textures/start.jpg";
const static std::string CONTINUER_TEXT_PATH = "/assets/textures/continuer.jpg";
const static std::string RESTART_TEXT_PATH = "/assets/textures/restart.jpg";
const static std::string nb0_TEXT_PATH = "/assets/textures/0.png";
const static std::string nb1_TEXT_PATH = "/assets/textures/1.png";
const static std::string nb2_TEXT_PATH = "/assets/textures/2.png";
const static std::string nb3_TEXT_PATH = "/assets/textures/3.png";
const static std::string nb4_TEXT_PATH = "/assets/textures/4.png";
const static std::string nb5_TEXT_PATH = "/assets/textures/5.png";
const static std::string nb6_TEXT_PATH = "/assets/textures/6.png";
const static std::string nb7_TEXT_PATH = "/assets/textures/7.png";
const static std::string nb8_TEXT_PATH = "/assets/textures/8.png";
const static std::string nb9_TEXT_PATH = "/assets/textures/9.png";
const static std::string ALIEN_TEXT_PATH = "/assets/textures/alien.jpg";
const static std::string ALIEN2_TEXT_PATH = "/assets/textures/alien2.jpg";
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

const static std::string TXT_FILE_PATH = "/map/items.json";


Game::Game(std::string dirPath, SDLWindowManager* window) :
		sphere(1,32,16), w(window){
	Program program = loadProgram(dirPath + VS_SHADER_PATH,
								  dirPath + FS_SHADER_PATH);
	program.use();
	/*********************************
	 * HERE SHOULD COME THE INITIALIZATION CODE
	 *********************************/

	textures.insert(std::pair<std::string, Texture *>("floor",new Texture( dirPath + FLOOR_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("wall",new Texture( dirPath + WALL_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("skybox",new Texture( dirPath + SKYBOX_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("door",new Texture( dirPath + DOOR_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("key",new Texture( dirPath + KEY_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("heart",new Texture( dirPath + HEART_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("tresor",new Texture( dirPath + TRESOR_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("gris",new Texture( dirPath + GRIS_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("green",new Texture( dirPath + GREEN_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("light-blue",new Texture( dirPath + LIGHTBLUE_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("blue",new Texture( dirPath + BLUE_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("yellow",new Texture( dirPath + YELLOW_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("red",new Texture( dirPath + RED_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("black",new Texture( dirPath + BLACK_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("white",new Texture( dirPath + WHITE_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("cursor",new Texture( dirPath + CURSOR_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("fire",new Texture( dirPath + FIRE_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("start",new Texture( dirPath + START_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("mini_key",new Texture( dirPath + MINI_KEY_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("0",new Texture( dirPath + nb0_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("1",new Texture( dirPath + nb1_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("2",new Texture( dirPath + nb2_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("3",new Texture( dirPath + nb3_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("4",new Texture( dirPath + nb4_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("5",new Texture( dirPath + nb5_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("6",new Texture( dirPath + nb6_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("7",new Texture( dirPath + nb7_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("8",new Texture( dirPath + nb8_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("9",new Texture( dirPath + nb9_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("continuer",new Texture( dirPath + CONTINUER_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("restart",new Texture( dirPath + RESTART_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("alien",new Texture( dirPath + ALIEN_TEXT_PATH , program.getGLId())));
	textures.insert(std::pair<std::string, Texture *>("alien2",new Texture( dirPath + ALIEN2_TEXT_PATH , program.getGLId())));




	beginMenu = new BeginMenu("alien");
	endMenu = new EndMenu("alien2");
	currentMenu = beginMenu;
	menuDisplayed = true;

	std::string filePath = dirPath + TXT_FILE_PATH;

	t = Terrain(dirPath, &player, filePath);


	uMVPMatrix    = glGetUniformLocation(program.getGLId(),"uMVPMatrix");
	uMVMatrix     = glGetUniformLocation(program.getGLId(),"uMVMatrix");
	uNormalMatrix = glGetUniformLocation(program.getGLId(),"uNormalMatrix");
	uKd 	  	  = glGetUniformLocation(program.getGLId(),"uKd");
	uKs 	  	  = glGetUniformLocation(program.getGLId(),"uKs");
	uLightDir_vs    = glGetUniformLocation(program.getGLId(),"uLightDir_vs");
	uLightIntensity = glGetUniformLocation(program.getGLId(),"uLightIntensity");
	uIsTransparent = glGetUniformLocation(program.getGLId(),"uIsTransparent");


	ProjMatrix = glm::perspective(glm::radians(70.f), (float)w->getWidth()/(float)w->getHeight(), 0.1f, 100.f) * player.getViewMatrix();
	MVMatrix   = glm::translate(MVMatrix,glm::vec3(0,0,-5)) * player.getViewMatrix();
	NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

	glEnable(GL_DEPTH_TEST);
}

void Game::play(){
	// Application loop:
	glm::vec2 cursorPosition, cursorPositionInGL;
	bool done = false;
	while(!done) {
		Uint32 startTime = SDL_GetTicks();
		// Event loop:
		SDL_Event e;
		while(w->pollEvent(e)) {
			switch(e.type){
				case SDL_MOUSEMOTION:
					cursorPosition = w->getMousePosition();//glm::vec2(e.button.x, e.button.y);

					if(menuDisplayed){
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					cursorPositionInGL = w->getMousePositionInGL(cursorPosition);
					currentMenu->checkButtons(cursorPositionInGL, this);
					break;
				case SDL_KEYDOWN:
					t.keyEvent(e.key.keysym.sym) ;
					break;

				case SDL_QUIT:
					done = true; // Leave the loop after this iteration
					break;
			}
		}

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(cubes.getVao());

		glDisable(GL_TEXTURE_2D);
		glm::mat4 vm = player.getViewMatrix();

		ProjMatrix = glm::perspective(glm::radians(70.f), (float)w->getWidth()/(float)w->getHeight(), 0.1f, 100.f) * vm;
		MVMatrix   = glm::translate(MVMatrix,glm::vec3(0,0,-5)) * vm;

		if(menuDisplayed){
			drawMenu();
			drawMouseCursor(cursorPosition);
			w->swapBuffers();
			continue;
		}
		if(!t.update()){
			currentMenu = endMenu;
			menuDisplayed = true;
		}

		glm::mat4 MVMatrix;
		t.draw(this);
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if (elapsedTime < FRAMERATE_MILLISECONDS) {
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}

		w->swapBuffers();
	}
}

Game::~Game() {
}


void Game::drawSphere(std::string texture, glm::vec3 translate, float rotate, glm::vec3 scale){
	glm::mat4 MVMatrix;

	Texture *text = textures.at(texture);
	if(!text)
		return;

	glBindVertexArray(sphere.getVao());
	sphere.draw(text, translate, rotate, scale);
	glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * sphere.getModelMatrix()));
	glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
	glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

	glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0.7,0.7,0.7)));
	glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0.7,0.7,0.7)));
	glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(1,1,1)));
	glUniform3fv(uLightDir_vs, 1, glm::value_ptr(glm::vec3(player.getPosition().x*0.01,player.getPosition().y+1,player.getPosition().z*0.01)*glm::mat3(player.getViewMatrix())));
	glUniform1i(uIsTransparent, 0);

	glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
	glBindVertexArray(0);
}

void Game::drawCube(std::string texture, glm::vec3 translate, float rotate, glm::vec3 scale){
	glm::mat4 MVMatrix;

	Texture *text = textures.at(texture);
	if(!text)
		return;

	glBindVertexArray(cubes.getVao());
	cubes.draw(text, translate, rotate, scale);
	glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
	glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
	glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

	glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0.5,1,0.7)));
	glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0.5,1,0.7)));
	glUniform3fv(uLightDir_vs, 1, glm::value_ptr(glm::vec3((player.getPosition().x+1)*0.01,player.getPosition().y+1,(player.getPosition().z-0.5)*0.01)*glm::mat3(player.getViewMatrix())));
	glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(1,1,1)));
	glUniform1i(uIsTransparent, 0);

	glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());
	glBindVertexArray(0);
}

void Game::drawCube(std::string texture, glm::vec3 translate, float rotate, glm::vec3 scale, bool noLight){
	glm::mat4 MVMatrix;

	Texture *text = textures.at(texture);
	if(!text)
		return;

	glBindVertexArray(cubes.getVao());
	cubes.draw(text, translate, rotate, scale);
	glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
	glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
	glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

	glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform3fv(uLightDir_vs, 1, glm::value_ptr(glm::vec3(1,1,1)));
	glUniform1i(uIsTransparent, 0);
	glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());
	glBindVertexArray(0);
}

void Game::drawButton(Button *btn){
	std::string text = btn->getTexture();
	glm::vec3 pos(btn->getPosX(), btn->getPosY(), 0);
	glm::vec3 scale(btn->getWidth(), 0.1, btn->getHeight());
	drawCubeInterface(text, pos, 0, scale);
}

void Game::drawMouseCursor(glm::vec2 p){
	glm::vec3 pos(p.x/(float)w->getWidth(), -p.y/(float)w->getHeight(), 0);
	float size = 0.035;
	drawCubeInterface("cursor", glm::vec3(2*pos.x - 1,2*pos.y  +1,-1), -M_PI/2, glm::vec3(size, size, size));

}

void Game::drawMenu(){
	drawCubeInterface(currentMenu->getTexture(), glm::vec3(0,0,-1), 0, glm::vec3(1	, 1	, 1	));
	currentMenu->draw(this);

}

void Game::drawCubeInterface(std::string texture, glm::vec3 translate, float rotate, glm::vec3 scale){
	glm::mat4 MVMatrix;

	Texture *text = textures.at(texture);
	if(!text)
		return;

	glBindVertexArray(cubes.getVao());
	cubes.draw(text, translate, rotate, scale);
	glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(glm::mat4(1) * cubes.getModelMatrix()));
	glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
	glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

	glUniform1i(uIsTransparent, 1);
	glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform3fv(uLightDir_vs, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());
	glBindVertexArray(0);
}

void Game::start(){
	menuDisplayed = false;
}

void Game::next(){
	t.next();
	menuDisplayed = false;
}

void Game::restart(){
	t.restart();
	menuDisplayed = false;
}
