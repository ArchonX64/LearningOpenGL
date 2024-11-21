//
// Created by kgil2 on 9/10/2024.
//

#include "BlockRenderer.h"

BlockRenderer::BlockRenderer() : VAO(0) {
    shader = std::make_unique<Shader>(vertPath, fragPath);

    // Initialize vertex array
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Get shader locations
    this->shader->use();
    modelLoc = this->shader->getLoc("model");
    viewLoc = this->shader->getLoc("view");
    projLoc = this->shader->getLoc("projection");

    // Set texture binding
    this->shader->setInt("texture0", 0);
}


void BlockRenderer::renderAll(Sptr<Texture> texture, std::vector<glm::vec3> locs, glm::mat4 view, glm::mat4 proj) {
    glActiveTexture(GL_TEXTURE0);

    texture->bind();
    shader->use();

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    glBindVertexArray(VAO);
    for(glm::vec3 model : locs) {

        auto modelMat = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                           glm::value_ptr(glm::translate(modelMat, model)));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);

}
