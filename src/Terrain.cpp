#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../include/Terrain.hpp"
#include "../include/Pixels.hpp"
#include <fstream>

namespace glimac {

Terrain::Terrain() {
    this->path = "";
    this->width = 0;
    this->height = 0;
    this->loadMap();
}

Terrain::Terrain(std::string _path) {
    this->path = _path;
    this->width = 0;
    this->height = 0;
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

void Terrain::loadMap() {
    std::ifstream file("/Users/Matthieu/Desktop/projet/bin/map/map2.ppm");
    if (file)
    {
        std::cout << "YES, the map has been loaded successfully." << std::endl;
        std::string content;
        getline(file, content);
        getline(file, content);
        getline(file, content);
        int i = 0;
        std::string nbzones = "";
        while (content[i] != ' ')
        {
            nbzones += content[i];
            i++;
        }

        int zones = stoi(nbzones);
        this->width = zones;
        this->height = zones;
        getline(file, content);
        Pixels a = Pixels();
        for (int i = 0; i < zones; i++) {
            for (int j = 0; j < zones; j++){
                getline(file, content);
                a.setRed(std::stoi(content));
                getline(file, content);
                a.setGreen(std::stoi(content));
                getline(file, content);
                a.setBlue(std::stoi(content));
                this->pixels.push_back(a);
            }
        }
        file.close();
    }
    else std::cerr << "Impossible de lire de fichier." << std::endl;
}

std::vector<Pixels> Terrain::getPixels() {
    return this->pixels;
}

}
