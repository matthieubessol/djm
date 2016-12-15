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
#include "Texture.hpp"

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
    Program program = loadProgram(applicationPath.dirPath() + "/shaders/3D.vs.glsl",
                                  applicationPath.dirPath() + "/shaders/multiTex3D.fs.glsl");
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    std::vector<std::string> stringTextures;
    stringTextures.push_back(applicationPath.dirPath() + "/assets/textures/EarthMap.jpg");
    stringTextures.push_back(applicationPath.dirPath() + "/assets/textures/MoonMap.jpg");

    Cube cubes = Cube(program.getGLId(), stringTextures);
    Terrain t = Terrain();
    Player player;
    glm::vec3 start = glm::vec3(t.getStartPosition().z, 0, t.getStartPosition().x);
    player.getCamera()->setPosition(start);

    GLint uMVPMatrix    = glGetUniformLocation(program.getGLId(),"uMVPMatrix");
    GLint uMVMatrix     = glGetUniformLocation(program.getGLId(),"uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(),"uNormalMatrix");

    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f) * player.getCamera()->getViewMatrix();
    MVMatrix   = glm::translate(MVMatrix,glm::vec3(0,0,-5)) * player.getCamera()->getViewMatrix();
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // // LOAD THE TEXTURE
    // std::unique_ptr<Image> earth = loadImage(applicationPath.dirPath() + "/assets/textures/EarthMap.jpg");
    // if(earth == NULL) {
    //     std::cout << "Can't open it" << std::endl;
    // }
    // GLuint textureEarth;
    // glGenTextures(1,&textureEarth);
    // glBindTexture(GL_TEXTURE_2D, textureEarth);
    // glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,earth->getWidth(),earth->getHeight(),0,GL_RGBA,GL_FLOAT,earth->getPixels());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Texture textureEarth = Texture(applicationPath.dirPath() + "/assets/textures/EarthMap.jpg", program.getGLId());
    Texture textureMoon  = Texture(applicationPath.dirPath() + "/assets/textures/MoonMap.jpg", program.getGLId());

    std::unique_ptr<Image> cloudz = loadImage(applicationPath.dirPath() + "/assets/textures/CloudMap.jpg");
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

    // GLint uEarthTexture = glGetUniformLocation(program.getGLId(), "uEarthTexture");
    GLint uCloudTexture = glGetUniformLocation(program.getGLId(), "uCloudTexture");

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)  {
                    case SDLK_UP :
                        if(t.checkCollision(player.getCamera()->getFuturePosition(1)) == true)
                            player.getCamera()->moveFront(player.getCamera()->getMoveFrontValue());
                        break;
                    case SDLK_DOWN :
                        if(t.checkCollision(player.getCamera()->getFuturePosition(-1)) == true)
                            player.getCamera()->moveFront(-player.getCamera()->getMoveFrontValue());
                        break;
                    case SDLK_LEFT :
                        player.getCamera()->rotateLeft(player.getCamera()->getAngleValue());
                        break;
                    case SDLK_RIGHT :
                        player.getCamera()->rotateLeft(-player.getCamera()->getAngleValue());
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
        glUniform1i(textureEarth.getUTexture(), 0);
        glUniform1i(uCloudTexture, 1);
        cubes.resetMatrix();
        cubes.drawPlane(textureEarth.getActiveTexture(), textureEarth.getidTexture(), (t.getWidth()/2) + 1, t.getWidth()/2, t.getHeight()/2);
        glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
        glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());

        int nbCount = 0;
        for (int j = 0; j < t.getWidth(); ++j){
            for(int i = 0; i < t.getHeight(); ++i) {
                if(t.getPixels().at(nbCount).isRed()) {
                    cubes.draw(textureMoon.getActiveTexture(), textureMoon.getidTexture(), i , j);
                } else {
                    cubes.resetMatrix();
                }
                glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
                glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());
                nbCount++;
            }
        }

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    unsigned int earth = int(textureEarth.getidTexture());
    unsigned int moon =  int(textureEarth.getidTexture());

    glDeleteTextures(0,&earth);
    glDeleteTextures(0,&moon);
    return EXIT_SUCCESS;
}
