//
// Created by kgil2 on 10/16/2024.
//

#include "BoxRenderer.h"

#include <utility>


BoxRenderer::BoxRenderer(std::weak_ptr<Window> window) : window(std::move(window)) {
    shader = std::make_unique<Shader>("../src/shaders/box_v.glsl", "../src/shaders/box_f.glsl");

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader->use();
    sizeLoc = shader->getLoc("size");
    modelLoc = shader->getLoc("model");
    viewLoc = shader->getLoc("view");
    projectionLoc = shader->getLoc("projection");

    shader->setInt("texture0", 0);
}


void BoxRenderer::renderFlatBox(int x, int y, int width, int height) {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window->getWidth()),
                                      0.0f, static_cast<float>(window->getHeight()));
    glUniform2f(sizeLoc, width, height);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
}