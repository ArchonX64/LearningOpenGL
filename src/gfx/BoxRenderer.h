//
// Created by kgil2 on 10/16/2024.
//

#ifndef GLFW2_BOXRENDERER_H
#define GLFW2_BOXRENDERER_H

#include <string>

#include "Window.h"
#include "Shader.h"
#include "FontRenderer.h"

#include "../util.h"

class Window;

class BoxRenderer {
    Uptr<Shader> shader;
    std::weak_ptr<Window> window;
    unsigned int VBO;
    unsigned int VAO;
    int sizeLoc;
    int modelLoc;
    int viewLoc;
    int projectionLoc;
public:
    BoxRenderer(std::weak_ptr<Window> window);

    void renderFlatBox(int x, int y, int width, int height);
    void renderFlatTextBox(const std::string& s, const Uptr<FontRenderer>& fontRenderer,
                           int x, int y, int width, int height);
    void renderBox(int x, int y, int z, int width, int height);
    void renderFlatTextBox(const std::string& s, const Uptr<FontRenderer>& fontRenderer,
                           int x, int y, int z, int width, int height, int screenWidth, int screenHeight);

    constexpr const static float vertices[] = {
            -0.5, 0.5, 0.0, 1.0,
            -0.5, -0.5, 0.0, 0.0,
            0.5, -0.5, 1.0, 0.0,
            0.5, 0.5, 1.0, 1.0
    };
};


#endif //GLFW2_BOXRENDERER_H
