#pragma once

#include <GL/glew.h>

#include "glimac/common.hpp"
#include <glimac/Program.hpp>
#include "Pixels.hpp"

namespace glimac {

class Texture {
private:
    std::string path;
    GLuint activeTexture;
    GLuint idTexture;
    GLuint uTexture;

public:
    Texture(std::string _path, GLuint glId);
    ~Texture();
    GLuint getActiveTexture();
    GLuint getidTexture();
    GLuint getUTexture();
};

}
