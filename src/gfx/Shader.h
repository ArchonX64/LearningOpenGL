//
// Created by kgil2 on 8/31/2024.
//

#ifndef GLFW2_SHADER_H
#define GLFW2_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../util.h"

class Shader {
public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use();
    int getLoc(const std::string& value);
    void setBool(const std::string& name, bool value) const;
    void setFloat(const std::string& name, float value) const;
    void setInt(const std::string& name, int value) const;
};


#endif //GLFW2_SHADER_H
