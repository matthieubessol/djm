#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../include/Terrain.hpp"
#include <fstream>
#include <GL/glew.h>


// Terrain::Terrain() {
//     this->path = "";
//     this->width = 0;
//     this->height = 0;
//     this->startPosition = glm::vec3(0,0,0);
//     this->finishPosition = glm::vec3(0,0,0);
//     this->loadMap();
// }
namespace glimac{

    Terrain::Terrain(std::string _path) {
        this->path = _path;
        this->width = 0;
        this->height = 0;
        this->startPosition = glm::vec3(0,0,0);
        this->finishPosition = glm::vec3(0,0,0);
        this->loadMap();
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
        return this->startPosition;
    }

    void Terrain::loadMap() {
        std::ifstream file(path+"/map/map2.ppm");
        if (file){
            std::cout << "YES, the map has been loaded successfully." << std::endl;
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

            for (int i = 0; i < zones; i++) {
                for (int j = 0; j < zones; j++){
                    getline(file, content);
                    r = std::stoi(content);
                    getline(file, content);
                    g = std::stoi(content);
                    getline(file, content);
                    b = std::stoi(content);
                    Pixel *a= new Pixel(r, g, b);
                    if(a->isWhite())
                        this->startPosition = glm::vec3(i,0,j);
                    if(a->isGreen() && a->isWhite() == false)
                        this->finishPosition = glm::vec3(i,0,j);
                    this->pixels.push_back(a);
                }
            }
            file.close();
        }
        else std::cerr << "Impossible de lire de fichier." << std::endl;
    }

//    std::vector<Pixel*> Terrain::getPixels() {
//        return this->pixels;
//    }

    bool Terrain::checkCollision(glm::vec3 playerPosition) {
        if(playerPosition.z == finishPosition.x && playerPosition.x == finishPosition.z ) {
            std::cout << "WIN" << std::endl;
        }

bool Terrain::checkCollision(glm::vec3 playerPosition) {
    if(!this->isInTerrain(playerPosition)) return true;
    if(this->pixels.at(int(playerPosition.z+0.01) * width + int(playerPosition.x))->isRed() == false && int(playerPosition.z+0.01) <= this->getWidth() && int(playerPosition.z+0.01) >= 0 && int(playerPosition.x+0.01) >= 0 && int(playerPosition.x+0.01) < this->getHeight()) {
        return false;
    }
    return true;
}

bool Terrain::checkReachEnd(glm::vec3 playerPosition) {
    if(playerPosition.z == finishPosition.x && playerPosition.x == finishPosition.z ) {
        return true;
    return false;
}

bool Terrain::isWall(int pos){
	return pixels.at(pos)->isRed();
}

bool Terrain::isInTerrain(glm::vec3 playerPosition) {
    if(int(playerPosition.z+0.01) < this->getWidth() && playerPosition.z >= 0 && playerPosition.x >= 0 && playerPosition.x < this->getHeight())
        return true;
    return false;
}

}
