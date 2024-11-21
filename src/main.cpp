//
// Created by kgil2 on 8/30/2024.
//
#include <memory>

#include "gfx/Window.h"
#include "gfx/Shader.h"
#include "gfx/BlockRenderer.h"
#include "gfx/BoxRenderer.h"


int main() {
    Window::init();
    auto winstance = std::make_shared<Window>("MyWin", 800, 600, 165);
    auto boxRenderer = std::make_unique<BoxRenderer>(winstance);
    auto tex = std::make_shared<Texture>("../res/textures/grass_full.png", GL_REPEAT,
                                         GL_NEAREST_MIPMAP_NEAREST,GL_NEAREST);
    std::vector<glm::vec3> locs =
    { glm::vec3(2.5, 0.0, -2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0) };

    winstance->windowMainLoop(tex, locs);

    return 0;
}