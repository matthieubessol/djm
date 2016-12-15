#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <vector>
#include "Cube.hpp"
#include "Player.hpp"
#include "Terrain.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram("/Users/Matthieu/Desktop/projet/bin/shaders/3D.vs.glsl",
                                  "/Users/Matthieu/Desktop/projet/bin/shaders/multiTex3D.fs.glsl");
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    Player player;
    Cube cubes;

    GLint uMVPMatrix    = glGetUniformLocation(program.getGLId(),"uMVPMatrix");
    GLint uMVMatrix     = glGetUniformLocation(program.getGLId(),"uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(),"uNormalMatrix");

    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f) * player.getCamera()->getViewMatrix();
    MVMatrix   = glm::translate(MVMatrix,glm::vec3(0,0,-5)) * player.getCamera()->getViewMatrix();
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    std::vector<glm::vec3> rotateValues;
    for (int i = 0; i < 32; ++i){
        glm::vec3 value = glm::sphericalRand(3.f);
        // rotateValues.push_back(glm::sphericalRand(3));
        rotateValues.push_back(value);
    }

    // LOAD THE TEXTURE
    std::unique_ptr<Image> earth = loadImage("/Users/Matthieu/Desktop/OpenGL/workspace/TP8/assets/textures/EarthMap.jpg");
    if(earth == NULL) {
        std::cout << "Can't open it" << std::endl;
    }
    GLuint textureEarth;
    glGenTextures(1,&textureEarth);
    glBindTexture(GL_TEXTURE_2D, textureEarth);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,earth->getWidth(),earth->getHeight(),0,GL_RGBA,GL_FLOAT,earth->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::unique_ptr<Image> moon = loadImage("/Users/Matthieu/Desktop/OpenGL/workspace/TP8/assets/textures/MoonMap.jpg");
    if(moon == NULL) {
        std::cout << "Can't open it" << std::endl;
    }
    GLuint textureMoon;
    glGenTextures(1,&textureMoon);
    glBindTexture(GL_TEXTURE_2D, textureMoon);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,moon->getWidth(),moon->getHeight(),0,GL_RGBA,GL_FLOAT,moon->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::unique_ptr<Image> cloudz = loadImage("/Users/Matthieu/Desktop/OpenGL/workspace/TP8/assets/textures/CloudMap.jpg");
    if(cloudz == NULL) {
        std::cout << "Can't open it" << std::endl;
    }
    GLuint textureCloudz;
    glGenTextures(1,&textureCloudz);
    glBindTexture(GL_TEXTURE_2D, textureCloudz);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,cloudz->getWidth(),cloudz->getHeight(),0,GL_RGBA,GL_FLOAT,cloudz->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_DEPTH_TEST);

    GLint uEarthTexture = glGetUniformLocation(program.getGLId(), "uEarthTexture");
    GLint uCloudTexture = glGetUniformLocation(program.getGLId(), "uCloudTexture");

    Terrain t = Terrain();

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_MOUSEWHEEL) {
                player.getCamera()->moveFront(e.wheel.y);
            }
            if(e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)  {
                    case SDLK_UP :
                        player.getCamera()->moveFront(1);
                        break;
                    case SDLK_DOWN :
                        player.getCamera()->moveFront(-1);
                        break;
                    case SDLK_LEFT :
                        player.getCamera()->rotateLeft(90);
                        break;
                    case SDLK_RIGHT :
                        player.getCamera()->rotateLeft(-90);
                        break;
                    default:
                        break;
                }
                break;
            }
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

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

        glUniform1i(uEarthTexture, 0);
        glUniform1i(uCloudTexture, 1);

        int nbCount = 0;
        for (int i = 0; i < t.getWidth(); ++i){
            for(int j = 0; j < t.getHeight(); ++j) {
                if(t.getPixels().at(nbCount).isRed()) {
                    cubes.draw(GL_TEXTURE1, textureMoon, i , j);
                    glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
                glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                } else {
                    cubes.resetMatrix();
                    // cubes.draw(GL_TEXTURE0, textureEarth, i , j);
                }

                glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
                glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));


                nbCount++;
            }
        }

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteTextures(0,&textureMoon);
    glDeleteTextures(0,&textureEarth);
    return EXIT_SUCCESS;
}
