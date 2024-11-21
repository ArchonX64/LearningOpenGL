//
// Created by kgil2 on 8/31/2024.
//

#include "Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        util::log(util::LogLevel::ERROR, "Failed to read shader files!");
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    const char* vertexC = vertexCode.c_str();
    const char* fragmentC = fragmentCode.c_str();
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    std::stringstream errorStream;

    // Compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexC, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        errorStream << "Failed to compiles vertex shader! Output log:\n" << infoLog;
        util::log(util::LogLevel::ERROR, errorStream.str());
        exit(-1);
    }

    // Compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentC, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        errorStream << "Failed to compiles fragment shader! Output log:\n" << infoLog;
        util::log(util::LogLevel::ERROR, errorStream.str());
        exit(-1);
    }

    // Link Shader
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        errorStream << "Failed to link shader program! Output log\n" << infoLog;
        util::log(util::LogLevel::ERROR, errorStream.str());
        exit(-1);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::use() {
    glUseProgram(ID);
}

int Shader::getLoc(const std::string& value) {
    int result = glGetUniformLocation(ID, value.c_str());
    if(result == -1) {
        util::log(util::LogLevel::EXCEPTION, "Failed to get uniform location of text: ");
        std::cout << value << std::endl;
        exit(-1);
    }
    return result;
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}