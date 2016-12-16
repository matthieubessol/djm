#pragma once

#include <vector>

#include "glimac/common.hpp"
#include "glimac/FreeflyCamera.hpp"
#include "Pixel.hpp"
#include "Bonus.h"

namespace glimac{
    // Représente un cube discrétisée centrée en (0, 0, 0) (dans son repère local)
    // Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
    class Terrain {
    private:
        std::string path;
        int width;
        int height;
        std::vector<Pixel*> pixels;
        glm::vec3 startPosition;
        glm::vec3 finishPosition;
        std::vector<Bonus*> bonus;
        // std::vector< std::vector<int> > matriceMap;

    public:
        // Constructeur: alloue le tableau de données et construit les attributs des vertex
        //Terrain();
        Terrain(std::string _path);
        ~Terrain();
        int getWidth();
        int getHeight();
        //std::vector<Pixel*> getPixels();
        void loadMap();
        glm::vec3 getStartPosition();
        bool isWall(int pos);
        bool checkCollision(glm::vec3 playerPosition);
        bool checkReachEnd(glm::vec3 playerPosition);
        bool isInTerrain(glm::vec3 playerPosition);
    };
}
