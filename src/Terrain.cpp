#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "glimac/common.hpp"
#include "Terrain.hpp"
#include <fstream>
#include <GL/glew.h>
#include "Player.hpp"
#include "Game.h"


static const std::string MAP_PATH = "/map/map.ppm";


Terrain::Terrain(){
	this->width = 0;
	this->height = 0;
	this->startPosition = glm::vec2(0,0);
	this->finishPosition = glm::vec2(0,0);
	player = NULL;
}

Terrain::Terrain(std::string _path, Player* p) {
	this->path = _path;
	this->width = 0;
	this->height = 0;
	this->startPosition = glm::vec2(0,0);
	this->finishPosition = glm::vec2(0,0);
	this->loadMap();
	linkDoors();
	player = p;
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

void Terrain::loadMap() {
	std::ifstream file(path+MAP_PATH);
	if (file){
		std::string content;
		getline(file, content);
		getline(file, content);
		getline(file, content);
		int i = 0;
		std::string nbzones = "";
		while (content[i] != ' '){
			nbzones += content[i];
			i++;
		}
		int zones = stoi(nbzones);
		this->width = zones;
		this->height = zones;
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
		this->startPosition = glm::vec2(x,y);
		return;
	}
	if(p->isEnd()){
		this->finishPosition = glm::vec2(x,y);
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
		if(player->hasItem(item)){
			removeDoor(d);
			return false;
		}
		return true;
	}
	if(isInTheSameCase(finishPosition, position)){
		std::cout<<"HOURA ! T'as trouve la sortie copain"<<std::endl;
		return false;
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

bool Terrain::isInTheSameCase(glm::vec2& pos1, glm::vec3& pos2){
	//glm::vec2 pos1_2D = get2DIntPosition(pos1);
	glm::vec2 pos2_2D = get2DIntPosition(pos2);
	return(pos1 == pos2_2D);
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


void Terrain::update(){
	for (unsigned int i=0; i<ennemis.size(); ++i){
			ennemis.at(i)->moov(this);
	}
}

void Terrain::draw(Game *g){
	drawKeys(g);
	drawWalls(g);
	drawDoors(g);
	drawBonus(g);
	drawEnnemis(g);
}

void Terrain::drawKeys(Game *g){
	for (unsigned int i=0; i<keys.size();++i){
		g->drawSphere("key", keys.at(i)->getPosition(), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.2, 0.2));
	}
}

void Terrain::drawBonus(Game *g){
	for (unsigned int i=0; i<bonus.size();++i){
		g->drawSphere("bonus", bonus.at(i)->getPosition(), glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5));
	}
}

void Terrain::drawWalls(Game *g){
	for (unsigned int i=0; i<walls.size();++i){
		g->drawCube("wall", walls.at(i)->getPosition(), glm::vec3(0, 0, 0), glm::vec3(0.5, 2, 0.5));
	}
}

void Terrain::drawDoors(Game *g){
	for (unsigned int i=0; i<doors.size();++i){
		g->drawCube("door", doors.at(i)->getPosition(), glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5));
	}
}

void Terrain::drawEnnemis(Game *g){
	for (unsigned int i=0; i<ennemis.size();++i){
		g->drawSphere("key", ennemis.at(i)->getPosition(), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.2, 0.2));
	}
}

