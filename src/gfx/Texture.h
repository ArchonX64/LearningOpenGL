//
// Created by kgil2 on 9/6/2024.
//

#ifndef GLFW2_TEXTURE_H
#define GLFW2_TEXTURE_H

#include <stb_image.h>

#include <string>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../util.h"

class Texture {
    unsigned int ID;
    std::string path;
    int width;
    int height;
    int nrChannels;
public:
    Texture(const std::string& path, GLint wrap, GLint minFilter, GLint magFilter);
    ~Texture();
    void bind();
    int getWidth();
    int getHeight();
    int getChannels();
};


#endif //GLFW2_TEXTURE_H
