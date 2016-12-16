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

const static std::string VS_SHADER_PATH = "/shaders/3D.vs.glsl";
const static std::string FS_SHADER_PATH = "/shaders/multiTex3D.fs.glsl";
const static std::string EARTH_TEXT_PATH = "/assets/textures/EarthMap.jpg";
const static std::string MOON_TEXT_PATH = "/assets/textures/MoonMap.jpg" ;
const static std::string SKYBOX_TEXT_PATH = "/assets/textures/skybox.jpg";


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
    std::cout<<"direpath : "<<applicationPath.dirPath()<<std::endl;
    Program program = loadProgram(applicationPath.dirPath() + VS_SHADER_PATH,
                                  applicationPath.dirPath() + FS_SHADER_PATH);
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    // std::vector<std::string> stringTextures;
    // stringTextures.push_back(applicationPath.dirPath() + "/assets/textures/EarthMap.jpg");
    // stringTextures.push_back(applicationPath.dirPath() + "/assets/textures/MoonMap.jpg");
    std::vector<Texture *> textures;
    textures.push_back( new Texture( applicationPath.dirPath() + EARTH_TEXT_PATH , program.getGLId()) );
    textures.push_back( new Texture( applicationPath.dirPath() + MOON_TEXT_PATH , program.getGLId()) );
    textures.push_back( new Texture( applicationPath.dirPath() + SKYBOX_TEXT_PATH ,program.getGLId()) );

    Cube cubes;
    Terrain t = Terrain(applicationPath.dirPath());
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

    glEnable(GL_DEPTH_TEST);

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

        cubes.draw(textures.at(2), glm::vec3(t.getWidth()/2,0,t.getHeight()/2), windowManager.getTime(), glm::vec3(1,1,1), glm::vec3(t.getWidth(),t.getWidth(),t.getWidth()));
        glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
        glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());

        cubes.draw(textures.at(0), glm::vec3(t.getWidth()/2,-0.6,t.getHeight()/2), windowManager.getTime(), glm::vec3(1,1,1), glm::vec3(t.getWidth()/2,0.1,t.getHeight()/2));
        glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
        glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());

        int nbCount = 0;
        for (int j = 0; j < t.getWidth(); ++j){
            for(int i = 0; i < t.getHeight(); ++i) {
                if(t.isWall(nbCount)) {
                    cubes.draw(textures.at(1), i , j);
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
        windowManager.swapBuffers();
    }
    return EXIT_SUCCESS;
}
