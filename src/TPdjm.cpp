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

    Player player = Player();

    Cube sphere = Cube();

    // VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,sphere.getVertexCount()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    // VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_POSITION_LOCATION = 0;
    const GLuint VERTEX_NORMAL_LOCATION = 1;
    const GLuint VERTEX_TEXTURE_LOCATION = 2;
    glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);
    glEnableVertexAttribArray(VERTEX_NORMAL_LOCATION);
    glEnableVertexAttribArray(VERTEX_TEXTURE_LOCATION);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) 0);
    glVertexAttribPointer(VERTEX_NORMAL_LOCATION  , 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_TEXTURE_LOCATION , 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)(offsetof(ShapeVertex, texCoords)));
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

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
                        player.getCamera()->moveFront(2);
                        break;
                    case SDLK_DOWN :
                        player.getCamera()->moveFront(-2);
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
        glBindVertexArray(vao);

        glm::mat4 vm = player.getCamera()->getViewMatrix();

        ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f) * vm;
        MVMatrix   = glm::translate(MVMatrix,glm::vec3(0,0,-5)) * vm;

        glm::mat4 MVMatrix;
        MVMatrix = glm::translate(MVMatrix,glm::vec3(0,0,-5));
        glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glUniform1i(uEarthTexture, 0);
        glUniform1i(uCloudTexture, 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureEarth); // la texture earthTexture est bindée sur l'unité GL_TEXTURE0
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureCloudz); // la texture cloudTexture est bindée sur l'unité GL_TEXTURE1

        glDrawArrays(GL_TRIANGLES,0, sphere.getVertexCount());

        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0

        int nbCount = 0;
        for (int i = 0; i < t.getWidth(); ++i){
            for(int j = 0; j < t.getHeight(); ++j) {

                if(t.getPixels().at(nbCount).isRed()) {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    glActiveTexture(GL_TEXTURE1);
                } else {
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    glActiveTexture(GL_TEXTURE0);
                }

                MVMatrix = glm::translate(glm::mat4(1), glm::vec3(i, 0, -j)); // Translation
                // MVMatrix = glm::rotate(MVMatrix, windowManager.getTime()+i, rotateValues[i]); // Translation * Rotation
                // MVMatrix = glm::translate(MVMatrix, glm::vec3(-rotateValues[i].y, rotateValues[i].x, 0)); // Translation * Rotation * Translation
                MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale

                glUniformMatrix4fv(uMVPMatrix,    1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                glUniformMatrix4fv(uMVMatrix,     1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

                if(t.getPixels().at(nbCount).isRed()) {
                    glBindTexture(GL_TEXTURE_2D,textureMoon);
                } else {
                    glBindTexture(GL_TEXTURE_2D,textureEarth);
                }
                glUniform1i(glGetUniformLocation(program.getGLId(),"uEarthTexture"), 0);
                glDrawArrays(GL_TRIANGLES,0, sphere.getVertexCount());

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
