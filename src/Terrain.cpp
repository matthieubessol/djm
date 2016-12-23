#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "glimac/common.hpp"
#include "../include/Terrain.hpp"
#include "../include/Pixel.hpp"
#include <fstream>
#include <GL/glew.h>
#include "Player.hpp"

static const std::string MAP_PATH = "/map/map.ppm";

namespace glimac {
Terrain::Terrain(std::string _path) {
	this->path = _path;
	this->width = 0;
	this->height = 0;
	this->startPosition = glm::vec2(0,0);
	this->finishPosition = glm::vec2(0,0);
	this->loadMap();
	linkDoors();
}

Terrain::~Terrain() {
}

int Terrain::getWidth() {
	return this->width;
}
int Terrain::getHeight() {
	return this->height;
}

glm::vec3 Terrain::getStartCameraPosition() {
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
		std::cout << "door in : " << glm::vec2(x, y)<< std::endl;
		return;
	}
	if(p->isKey()){
		Key *key = new Key(glm::vec3(x, 0, y), p);
		keys.push_back(key);
		std::cout << "Key in : " << glm::vec2(x, y)<< std::endl;
		return;
	}
}

//Key* Terrain::findKey(Pixel* door){
//	std::cout << "test "<< std::endl;
//
//	for (int x = 0; x < width; x++){
//		for (int y = 0; y < height; y++) {
//			glm::vec2 pos(x, y);
//			Pixel *p = getPixel(pos);
//			std::cout << "key not found in : " << pos<< std::endl;
//			if(door->isMyKey(p)){
//				std::cout << "key find in : " << pos<< std::endl;
//				return new Key(glm::vec3(x, 0, y), );
//			}
//		}
//	}
//	throw std::invalid_argument("Map Missing Key");
//}

Key* Terrain::findKey(Door* door){
	for(std::vector<Key*>::iterator it = keys.begin(); it != keys.end(); it++){
		if((*it)->getColor()->isMyDoor(door->getColor()))
			return *it;
	}
	throw std::invalid_argument("Missing Key");
}

bool Terrain::checkCollision(glm::vec3 playerPosition, Player* player) {
	if(!isInTerrain(playerPosition)) {
		return true;
	}
	if(isWall(playerPosition)) {
		return true;
	}
	Key *k = recoverKey(playerPosition);
	if(k!=NULL){
		PlayerItem *item = dynamic_cast<PlayerItem*>(k);
		player->addItem(item);
		return false;
	}
	Door *d = getDoor(playerPosition);
	if(d){
		PlayerItem *item = dynamic_cast<PlayerItem*>(d->getKey());
		if(player->hasItem(item)){
			removeDoor(d);
			return false;
		}
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
		if(posEqualsIn2D(pos, p)){
			return keys.at(i);
		}
	}
	return NULL;
}

Door* Terrain::getDoor(glm::vec3 pos){
	for(unsigned int i=0; i<doors.size(); ++i){
		glm::vec3 p= doors.at(i)->getPosition();
		if(posEqualsIn2D(pos, p)){
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
	int x = static_cast<int>(pos.x+0.1);
	int y = static_cast<int>(pos.z+0.1);
	return glm::vec2(x, y);
}

bool Terrain::posEqualsIn2D(glm::vec3& pos1, glm::vec3& pos2){
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



}
