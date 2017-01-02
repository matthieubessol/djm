#include <cmath>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdexcept>

#include "glimac/common.hpp"
#include "Terrain.hpp"
#include <fstream>
#include <GL/glew.h>
//#include <GLUT/glut.h>
#include "Player.hpp"
#include "Game.h"

static const int NB_MAPS = 3;
static const std::string MAP_1 = "/map/mapt.ppm";
static const std::string MAP_2 = "/map/map2.ppm";
static const std::string MAP_3 = "/map/map3.ppm";
static const int TRESOR_VALUE = 5;
static const float HEART_OFFSET = 0.1;
static const float KEY_OFFSET = 0.15;

Terrain::Terrain(){
	this->width = 0;
	this->height = 0;
	player = NULL;
}

Terrain::Terrain(std::string _imgPath, Player* p, std::string filePath) {
	this->imgPath = _imgPath;
	this->width = 0;
	this->height = 0;
	maps.push_back(MAP_1);
	maps.push_back(MAP_2);
	maps.push_back(MAP_3);
	indMap = 0;
	player = p;
	init();

	//chargement fichier json
//	std::ifstream file(filePath);
//	file >> json;
//	Json::iterator it;
//	std::cout << json.dump(4)<<"is array : "<<json.is_array() << std::endl;
//	for (auto& element : json) {
//		for ( it = element.begin(); it != element.end(); ++it) {
//		  std::cout << it.key() << " : " << it.value() << "\n";
//		}
//	}
}

void Terrain::init(){
//	if(mapIterator == maps.end()){
//		mapIterator = maps.begin();
//	}
	int ind = indMap%NB_MAPS;
	this->loadMap(maps.at(ind));
	linkDoors();
	player->setPosition(startPosition);
	thisIsTheEnd = false;
	indMap++;
}


Terrain::~Terrain() {
}

int Terrain::getWidth() {
	return this->width;
}
int Terrain::getHeight() {
	return this->height;
}

glm::vec3 Terrain::getStartPosition() {
	return glm::vec3(startPosition.x, 0, startPosition.y);
}

void Terrain::loadMap(std::string map) {
	std::ifstream file(imgPath+map);
	if (file){
		std::string content;
		getline(file, content);
		getline(file, content);
		getline(file, content);
		int i = 0;
		std::string w = "";
		std::string h = "";
		while (content[i] != ' '){
			w += content[i];
			i++;
		}
		i++;
		while (content[i] != ' '){
			h += content[i];
			i++;
		}
		this->width = (int) stoi(w);
		this->height = (int) stoi(h);
		getline(file, content);
		int r, g, b;
		for (int y = 0; y < height; y++) {
			std::vector<Pixel*> *ligne = new std::vector<Pixel*>();
			for (int x = 0; x < width; x++){
				getline(file, content);
				r = std::stoi(content);
				getline(file, content);
				g = std::stoi(content);
				getline(file, content);
				b = std::stoi(content);
				Pixel *a= new Pixel(r, g, b);
				checkPixelSignification(a, x, y);
				ligne->push_back(a);
			}
			pixels.push_back(ligne);
		}
		file.close();
		std::cout << "YES, the map has been loaded successfully." << std::endl;
		std::cout << "start pos : " << startPosition<< std::endl;
		for(unsigned int i=0; i<keys.size(); ++i){
			std::cout << "cle pos : " << keys.at(i)->getPosition()<< std::endl;
		}
	}
	else std::cerr << "Impossible de lire de fichier." << std::endl;
}

void Terrain::checkPixelSignification(Pixel* p, int x, int y){
	if(p->isStart()){
		this->startPosition = glm::vec3(x, 0, y);
		return;
	}
	if(p->isEnd()){
		this->finishPosition = glm::vec3(x, 0, y);
		return;
	}
	if(p->isDoor()){
		Door *door = new Door(glm::vec3(x, 0, y), p);
		doors.push_back(door);
		//std::cout << "door in : " << glm::vec2(x, y)<< std::endl;
		return;
	}
	if(p->isKey()){
		Key *key = new Key(glm::vec3(x, 0, y), p);
		keys.push_back(key);
		//std::cout << "Key in : " << glm::vec2(x, y)<< std::endl;
		return;
	}
	if(p->isEnnemi()){
		Ennemi *e = new Ennemi(glm::vec3(x, 0, y));
		ennemis.push_back(e);
		//std::cout << "ennemi in : " << glm::vec2(x, y)<< std::endl;
		return;
	}
	if(p->isWall()){
		SceneElement *e = new SceneElement(glm::vec3(x, 0, y));
		walls.push_back(e);
		//std::cout << "wall in : " << glm::vec2(x, y)<< std::endl;
		return;
	}
	if(p->isTresor()){
		SceneElement *e = new SceneElement(glm::vec3(x, 0, y));
		tresors.push_back(e);
		//std::cout << "wall in : " << glm::vec2(x, y)<< std::endl;
		return;
	}
}

std::string Terrain::getPixelSignificationString(Pixel* p){
	if(p->isStart()){
		return "green";
	}
	if(p->isEnd()){
		return "red";
	}
	if(p->isDoor()){
		return "blue";
	}
	if(p->isKey()){
		return "light-blue";
	}
	if(p->isEnnemi()){
		return "black";
	}
	if(p->isWall()){
		return "gris";
	}
	if(p->isTresor()){
		return "yellow";
	}
	return "black";
}



Key* Terrain::findKey(Door* door){
	for(std::vector<Key*>::iterator it = keys.begin(); it != keys.end(); it++){
		if((*it)->getColor()->isMyDoor(door->getColor()))
			return *it;
	}
	throw std::invalid_argument("Missing Key");
}

bool Terrain::checkCollision(glm::vec3 position, SceneElement *element) {
	//si c'est pas dans le terrain
	if(!isInTerrain(position)) {
		return true;
	}
	//si c'est un mur
	if(isWall(position)) {
		//std::cout<<"wall pos "<<playerPosition<<std::endl;
		return true;
	}
	//si c'est une clé
	Key *k = recoverKey(position);
	if(k!=NULL){
		PlayerItem *item = dynamic_cast<PlayerItem*>(k);
		player->addItem(item);
		return false;
	}
	//si c'est une porte
	Door *d = getDoor(position);
	if(d){
		PlayerItem *item = dynamic_cast<PlayerItem*>(d->getKey());
		if(player->findAndRemove(item)){
			removeDoor(d);
			return false;
		}
		return true;
	}
	//si c'est un trésor
	int money = recoveryTresor(position);
	if(money>0){
		player->addMoney(money);
		std::cout<<"player money = "<<player->getMoney()<<std::endl;
	}

	if(isEnd(position)){
		thisIsTheEnd = true;
	}

	// ennemis/players checks
	Player *_player = dynamic_cast<Player*>(element);
	if(!_player){
		if(isPlayer(position)){
			//std::cout<<"JE LE TUE !!!"<<std::endl;
			player->kill();
		}
	}
	else if(isEnnemi(position)){
		//std::cout<<"JE MEURS !!!"<<std::endl;
		player->kill();
		return true;
	}

	return false;
}

bool Terrain::checkReachEnd(glm::vec3 playerPosition) {
	if(playerPosition.x == finishPosition.x && playerPosition.z == finishPosition.y)
		return true;
	return false;
}

bool Terrain::isWall(glm::vec3 p){
	Pixel *color = getPixel(p);
	return (color->isWall());
}

bool Terrain::isDoor(glm::vec3 pos){
	if(!getPixel(pos)->isDoor())
		return false;
	Door *door= getDoor(pos);
	if(!door)
		return false;
	return true;
}

Key* Terrain::recoverKey(glm::vec3 pos){
	Key * k = getKey(pos);
	if(!isKey(pos))
		return NULL;
	removeKey(k);
	return k;
}

bool Terrain::isKey(glm::vec3 pos){
	if(!getPixel(pos)->isKey())
		return false;
	Key *key = getKey(pos);
	if(!key)
		return false;
	return true;
}

bool Terrain::isEnd(glm::vec3 pos){
	return getPixel(pos)->isEnd();
}

void Terrain::removeKey(Key* k){
	for(unsigned int i=0; i<keys.size(); ++i){
		if(keys.at(i) == k){
			keys.erase(keys.begin()+i);
			return;
		}
	}
}

void Terrain::removeDoor(Door* d){
	for(unsigned int i=0; i<doors.size(); ++i){
		if(doors.at(i) == d){
			doors.erase(doors.begin()+i);
			return;
		}
	}
}

Key* Terrain::getKey(glm::vec3 pos){
	for(unsigned int i=0; i<keys.size(); ++i){
		glm::vec3 p= keys.at(i)->getPosition();
		if(isInTheSameCase(pos, p)){
			return keys.at(i);
		}
	}
	return NULL;
}

Door* Terrain::getDoor(glm::vec3 pos){
	for(unsigned int i=0; i<doors.size(); ++i){
		glm::vec3 p= doors.at(i)->getPosition();
		if(isInTheSameCase(pos, p)){
			return doors.at(i);
		}
	}
	return NULL;
}

bool Terrain::isInTerrain(glm::vec3 pos) {
	return isInTerrain(get2DIntPosition(pos));
}

bool Terrain::isInTerrain(glm::vec2 pos) {
	return(pos.x>-1 && pos.x<width && pos.y>-1 && pos.y<height);
}

glm::vec2 Terrain::get2DIntPosition(glm::vec3& pos){
	int x = static_cast<int>(floor(pos.x+0.5));
	int y = static_cast<int>(floor(pos.z+0.5));
	return glm::vec2(x, y);
}

bool Terrain::isInTheSameCase(glm::vec3& pos1, glm::vec3& pos2){
	glm::vec2 pos1_2D = get2DIntPosition(pos1);
	glm::vec2 pos2_2D = get2DIntPosition(pos2);
	return(pos1_2D == pos2_2D);
}

Pixel* Terrain::getPixel(glm::vec3& p){
	glm::vec2 pos = get2DIntPosition(p);
	return getPixel(pos);
}


Pixel* Terrain::getPixel(glm::vec2& pos){
	if(!isInTerrain(pos)){
		exit(EXIT_FAILURE);
	}
	return pixels.at(pos.y)->at(pos.x);
}

void Terrain::linkDoors(){
	for(std::vector<Door*>::iterator it = doors.begin(); it != doors.end(); it++){
		(*it)->setKey(findKey(*it));
	}
}

bool Terrain::keyEvent(int  key){
	// Event loop:
	switch (key)  {
		case SDLK_UP :
			player->moovForward(this);
			break;
		case SDLK_DOWN :
			player->moovBack(this);
			break;
		case SDLK_LEFT :
			player->lookLeft();
			break;
		case SDLK_RIGHT :
			player->lookRight();
			break;
		default:
			break;
	}
	return false;
}

bool Terrain::isEnnemi(glm::vec3 pos){
	for (unsigned int i=0; i<ennemis.size(); ++i){
		glm::vec3 p =ennemis.at(i)->getPosition();
		if(isInTheSameCase(p, pos))
			return true;
	}
	return false;
}

bool Terrain::isPlayer(glm::vec3 pos){
	glm::vec3 p = player->getPosition();
	if(isInTheSameCase(p, pos))
		return true;
	return false;
}

bool Terrain::update(){
	for (unsigned int i=0; i<ennemis.size(); ++i){
			ennemis.at(i)->moov(this);
	}
	player->moveUpdate();
	if(thisIsTheEnd || player->isDead())
		return false;
	return true;
}

void Terrain::draw(Game *g){
	drawKeys(g);
	drawWalls(g);
	drawDoors(g);
	drawEnnemis(g);
	drawInterface(g);
	drawTresors(g);
	drawFloor(g);
	// drawSkyBox(g);
}

void Terrain::drawKeys(Game *g){
	for (unsigned int i=0; i<keys.size();++i){
		g->drawSphere("key", keys.at(i)->getPosition(), 0, glm::vec3(0.2, 0.2, 0.2));
	}
}

//void Terrain::drawBonus(Game *g){
//	for (unsigned int i=0; i<bonus.size();++i){
//		g->drawSphere("bonus", bonus.at(i)->getPosition(), 0, glm::vec3(0.5, 0.5, 0.5));
//	}

void Terrain::drawFloor(Game *g){
	int size = pixels.at(0)->size();
	for (unsigned int i=0; i<size;++i){
		for (unsigned int j=0; j<size;++j){
			g->drawCube("floor", glm::vec3(i,-0.5,j), 0, glm::vec3(0.5, 0.01, 0.5));
		}
	}
}


void Terrain::drawWalls(Game *g){
	for (unsigned int i=0; i<walls.size();++i){
		glm::vec3 pos = walls.at(i)->getPosition();
		g->drawCube("wall", glm::vec3(pos.x,0.5,pos.z), 0, glm::vec3(0.5, 1, 0.5));
	}
}

void Terrain::drawTresors(Game *g){
	for (unsigned int i=0; i<tresors.size();++i){
		g->drawCube("tresor", tresors.at(i)->getPosition(), -M_PI/2, glm::vec3(0.1, 0.1, 0.1));
	}
}

void Terrain::drawSkyBox(Game *g){
	int size = pixels.at(0)->size();
	g->drawCube("skybox", glm::vec3(size/2,0,size/2), 0, glm::vec3(size,size,size), true);
}

void Terrain::drawDoors(Game *g){
	for (unsigned int i=0; i<doors.size();++i){
		g->drawCube("door", doors.at(i)->getPosition(), 0, glm::vec3(0.5, 0.5, 0.5));
	}
}

void Terrain::drawEnnemis(Game *g){
	for (unsigned int i=0; i<ennemis.size();++i){
		g->drawSphere("fire", ennemis.at(i)->getPosition(), 0, glm::vec3(0.2, 0.2, 0.2));
	}
}

void Terrain::drawInterface(Game *g){
	float offset = 0.;
	for(int i=0; i < player->getNbLife(); i++){
		g->drawCubeInterface("heart", glm::vec3(-0.75+offset, 0.75, 0.1), -M_PI/2, glm::vec3(0.05, 0.05, 0.05));
		offset += HEART_OFFSET;
	}
	offset = 0.;
	for(int i=0; i < player->getNbKey(); i++){
		g->drawCubeInterface("mini_key", glm::vec3( 0.9-offset, -0.75, 0.1), -M_PI/2, glm::vec3(0.09, 0.09, 0.09));
		offset += KEY_OFFSET;
	}
	g->drawCubeInterface("tresor", glm::vec3(-0.75, 0.60, 0.1), -M_PI/2, glm::vec3(0.05, 0.05, 0.05));

	std::string moneyStr = std::to_string(player->getMoney());
	for (int i = 0; i < moneyStr.length(); ++i){
		g->drawCubeInterface(moneyStr.substr(i, 1).c_str(), glm::vec3(-0.62+0.1*i, 0.60, 0.1), -M_PI/2, glm::vec3(0.05, 0.05, 0.05));
	}

	drawMinimap(g);
}

void Terrain::drawMinimap(Game *g) {
	// Draw player.
	float scale = 0.015;
	g->drawCubeInterface("red", glm::vec3(0.5+scale+scale*player->getPosition().x, 0.5+19*scale-scale*player->getPosition().z, 0.1), -M_PI/2, glm::vec3(scale, scale/2, scale));

	for (unsigned int i=0; i<ennemis.size(); ++i){
		glm::vec3 p =ennemis.at(i)->getPosition();
		g->drawCubeInterface("black", glm::vec3(0.5+scale+scale*p.x, 0.5+19*scale-scale*p.z, 0.1), -M_PI/2, glm::vec3(scale, scale/2, scale));
	}
	for (unsigned int i=0; i<keys.size(); ++i){
		glm::vec3 p =keys.at(i)->getPosition();
		g->drawCubeInterface("blue", glm::vec3(0.5+scale+scale*p.x, 0.5+19*scale-scale*p.z, 0.1), -M_PI/2, glm::vec3(scale, scale/2, scale));
	}
	for (unsigned int i=0; i<tresors.size(); ++i){
		glm::vec3 p =tresors.at(i)->getPosition();
		g->drawCubeInterface("yellow", glm::vec3(0.5+scale+scale*p.x, 0.5+19*scale-scale*p.z, 0.1), -M_PI/2, glm::vec3(scale, scale/2, scale));
	}
	for (unsigned int i=0; i<walls.size(); ++i){
		glm::vec3 p =walls.at(i)->getPosition();
		g->drawCubeInterface("white", glm::vec3(0.5+scale+scale*p.x, 0.5+19*scale-scale*p.z, 0.1), -M_PI/2, glm::vec3(scale, scale/2, scale));
	}
	for (unsigned int i=0; i<doors.size(); ++i){
		glm::vec3 p =doors.at(i)->getPosition();
		g->drawCubeInterface("green", glm::vec3(0.5+scale+scale*p.x, 0.5+19*scale-scale*p.z, 0.1), -M_PI/2, glm::vec3(scale, scale/2, scale));
	}

//	float offsetX = 0, offsetY = 0;
//	for (int i = 0; i < pixels.at(0)->size(); i++){
//		offsetX += scale;
//		for (int j = pixels.at(0)->size() -1; j > 0; j--){
//			std::string type = getPixelSignificationString(pixels.at(j)->at(i));
//			if(type != "black")
//				g->drawCubeInterface(type, glm::vec3(-0.1+offsetX,-0.75+offsetY,-0.75), -M_PI/2, glm::vec3(scale, scale, scale));
//			offsetY += scale;
//		}
//		offsetY = 0;
//	}

}

int Terrain::recoveryTresor(glm::vec3 pos){
	for(unsigned int i=0; i<tresors.size(); ++i){
		glm::vec3 p= tresors.at(i)->getPosition();
		if(isInTheSameCase(pos, p)){
			tresors.erase(tresors.begin()+i);
			return TRESOR_VALUE;
		}
	}
	return 0;
}

void Terrain::next(){
	reset();
	init();
}

void Terrain::reset(){
	std::cout<<"reset"<<std::endl;
	for (std::vector<Door*>::iterator it = doors.begin() ; it != doors.end(); ++it){
		delete (*it);
	}
	doors.clear();

	for (std::vector<Key*>::iterator it = keys.begin() ; it != keys.end(); ++it){
		delete (*it);
	}
	keys.clear();

	for (std::vector<SceneElement*>::iterator it = walls.begin() ; it != walls.end(); ++it){
		delete (*it);
	}
	walls.clear();

	for (std::vector<SceneElement*>::iterator it = tresors.begin() ; it != tresors.end(); ++it){
		delete (*it);
	}
	tresors.clear();


	for (std::vector<Ennemi*>::iterator it = ennemis.begin() ; it != ennemis.end(); ++it){
		delete (*it);
	}
	ennemis.clear(); ;

	for(unsigned int i=0; i<pixels.size(); i++){
		for(unsigned int j=0; j<pixels.at(i)->size();++j){
			delete pixels.at(i)->at(j);
		}
		delete pixels.at(i);
	}
	pixels.clear();
	player->reset();
}
