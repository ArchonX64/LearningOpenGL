//
// Created by kgil2 on 8/30/2024.
//

#ifndef GLFW2_WINDOW_H
#define GLFW2_WINDOW_H

#include <string>
#include <functional>
#include <memory>
#include <iostream>
#include <iomanip>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../windows_f.h"

#include "Shader.h"
#include "Texture.h"
#include "BlockRenderer.h"
#include "BoxRenderer.h"
#include "Camera.h"
#include "FontRenderer.h"
#include "../util.h"

class BoxRenderer;

class Window {
private:
    GLFWwindow* window;
    Uptr<Camera> camera;
    Uptr<FontRenderer> fontRenderer;
    Uptr<BlockRenderer> blockRenderer;
    Uptr<BoxRenderer> boxRenderer;
    std::weak_ptr<Window> weak_this;

    double lastFrameTime;
    double deltaTime;
    double lastFps;
    bool isFullscreen;
    int refreshRate;
    int fps;
    unsigned long long memUse;
    int width;
    int height;
    int windowed_width;
    int windowed_height;
    int windowed_x;
    int windowed_y;
    bool paused;

    void cursorMoveCallback(double xpos, double ypos);
    void metricShow();
    void keyCallback(int key, int scancode, int action, int mods);
    void processInput();
public:
    const std::string name;
    static void init();

    explicit Window(std::string name, int width, int height, int refreshRate);
    ~Window();

    void windowMainLoop(const Sptr<Texture>& texture,
                        const std::vector<glm::vec3>& locs);

    double getDeltaTime() const;
    int getWidth() const;
    int getHeight() const;
};


#endif //GLFW2_WINDOW_H
