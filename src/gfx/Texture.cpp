//
// Created by kgil2 on 9/6/2024.
//

#include "Texture.h"

Texture::Texture(const std::string& path, GLint wrap, GLint minFilter, GLint magFilter) : path(path) {

    stbi_set_flip_vertically_on_load(true);
    unsigned char* texData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(!texData) {
        std::stringstream stream;
        stream << "Failed to load texture from path: " << path;
        util::log(util::LogLevel::ERROR, stream.str());
        exit(-1);
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texData);

}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

int Texture::getChannels() {
    return nrChannels;
}