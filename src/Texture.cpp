#include <glimac/Image.hpp>
#include <GL/glew.h>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "../include/Texture.hpp"
#include <fstream>
#include <glimac/Program.hpp>

namespace glimac {
Texture::Texture(std::string _path, GLuint glId) {
    std::unique_ptr<Image> img = loadImage(_path);
    if(img == NULL) {
        std::cout << "Can't open it" << std::endl;
    }

    glGenTextures(1,&this->idTexture);
    glBindTexture(GL_TEXTURE_2D, this->idTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img->getWidth(),img->getHeight(),0,GL_RGBA,GL_FLOAT,img->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    this->uTexture = glGetUniformLocation(glId, "uEarthTexture");
    glUniform1i(this->uTexture, 0);

    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    this->activeTexture = GL_TEXTURE0;
}

Texture::~Texture() {

}

GLuint Texture::getActiveTexture(){
    return this->activeTexture;
}

GLuint Texture::getidTexture(){
    return this->idTexture;
}

GLuint Texture::getUTexture(){
    return this->uTexture;
}

}
