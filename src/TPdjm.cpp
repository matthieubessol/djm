#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <iostream>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <vector>
#include <map>
#include "Cube.hpp"
#include "Player.hpp"
#include "Terrain.hpp"
#include "Texture.hpp"

using namespace glimac;

const static std::string VS_SHADER_PATH = "/shaders/3D.vs.glsl";
const static std::string FS_SHADER_PATH = "/shaders/multiTex3D.fs.glsl";
const static std::string FLOOR_TEXT_PATH = "/assets/textures/floor.jpg";
const static std::string WALL_TEXT_PATH = "/assets/textures/wall.jpg" ;
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

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    FilePath applicationPath(argv[0]);
    std::cout<<"direpath : "<<applicationPath.dirPath()<<std::endl;
    Program program = loadProgram(applicationPath.dirPath() + VS_SHADER_PATH,
                                  applicationPath.dirPath() + FS_SHADER_PATH);
    program.use();



    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    // std::vector<std::string> stringTextures;
    // stringTextures.push_back(applicationPath.dirPath() + "/assets/textures/EarthMap.jpg");
    // stringTextures.push_back(applicationPath.dirPath() + "/assets/textures/MoonMap.jpg");
    std::map<std::string, Texture *> textures;
    textures.insert(std::pair<std::string, Texture *>("floor",new Texture( applicationPath.dirPath() + FLOOR_TEXT_PATH , program.getGLId())));
    textures.insert(std::pair<std::string, Texture *>("wall",new Texture( applicationPath.dirPath() + WALL_TEXT_PATH , program.getGLId())));
    textures.insert(std::pair<std::string, Texture *>("skybox",new Texture( applicationPath.dirPath() + SKYBOX_TEXT_PATH , program.getGLId())));

    Cube cubes;
    Sphere sphere = Sphere(1,32,16);
    Terrain t = Terrain(applicationPath.dirPath());
    Player player;
    //glm::vec3 start = glm::vec3(t.getStartPosition().z, 0, t.getStartPosition().x);
    glm::vec3 start = t.getStartCameraPosition();
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
                    	player.moovForward(&t);
                    	break;
                    case SDLK_DOWN :
                    	player.moovBack(&t);
                        break;
                    case SDLK_LEFT :
                    	player.lookLeft();
                    	break;
                    case SDLK_RIGHT :
                        player.lookRight();
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

        cubes.draw(textures.at("skybox"), glm::vec3(t.getWidth()/2,0,t.getHeight()/2), windowManager.getTime(), glm::vec3(1,1,1), glm::vec3(t.getWidth(),t.getWidth(),t.getWidth()));
        glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
        glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());

        cubes.draw(textures.at("floor"), glm::vec3(t.getWidth()/2,-0.6,t.getHeight()/2), windowManager.getTime(), glm::vec3(1,1,1), glm::vec3(t.getWidth()/2,0.1,t.getHeight()/2));
        glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * cubes.getModelMatrix()));
        glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0, cubes.getVertexCount());

        glBindVertexArray(0);
        glBindVertexArray(sphere.getVao());
        sphere.draw(textures.at("floor"), glm::vec3(0,0,0), windowManager.getTime(), glm::vec3(0,0,0), glm::vec3(5,5,5));
        glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix * sphere.getModelMatrix()));
        glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glDrawArrays(GL_TRIANGLES,0, sphere.getVertexCount());
        glBindVertexArray(0);
        glBindVertexArray(cubes.getVao());
        int nbCount = 0;
            for (int y = 0; y < t.getHeight(); ++y){
            	for(int x = 0; x < t.getWidth(); ++x) {
                if(t.isWall(glm::vec3(x, 0, y))) {
                    cubes.draw(textures.at("wall"), x, y);
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
