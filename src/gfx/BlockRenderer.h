//
// Created by kgil2 on 9/10/2024.
//

#ifndef GLFW2_BLOCKRENDERER_H
#define GLFW2_BLOCKRENDERER_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>

//#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/string_cast.hpp>

#include "Shader.h"
#include "Texture.h"

class BlockRenderer {
public:
    inline static std::string vertPath = "../src/shaders/block_v.glsl";
    inline static std::string fragPath = "../src/shaders/block_f.glsl";
    constexpr const static float vertices[] = {
            // Each box represents one side of a block
            // Each line represents a point on a triangle, where there are
            //  two triangles for each side
            // The first three values represent the point coordinates
            // The next two values represent the desired texture coordinates
            // The last value represents the texture offset
            // The texture of a block is a single image, with each face coming
            // After the next. Therefore, you can get unique faces by just setting an offset.
            0.5f, -0.5f, -0.5f,  1.0f / 6, 0.0f, 0.0f / 6,
            -0.5f, -0.5f, -0.5f,  0.0f / 6, 0.0f, 0.0f / 6,
            0.5f,  0.5f, -0.5f,  1.0f / 6, 1.0f, 0.0f / 6,
            -0.5f,  0.5f, -0.5f,  0.0f / 6, 1.0f, 0.0f / 6,
            0.5f,  0.5f, -0.5f,  1.0f / 6, 1.0f, 0.0f / 6,
            -0.5f, -0.5f, -0.5f,  0.0f / 6, 0.0f,  0.0f / 6, // Front

            -0.5f, -0.5f,  0.5f,  1.0f / 6, 0.0f, 2.0f / 6,
            0.5f, -0.5f,  0.5f,  0.0f / 6, 0.0f, 2.0f / 6,
            0.5f,  0.5f,  0.5f,  0.0f / 6, 1.0f, 2.0f / 6,
            0.5f,  0.5f,  0.5f,  0.0f / 6, 1.0f, 2.0f / 6,
            -0.5f,  0.5f,  0.5f,  1.0f / 6, 1.0f, 2.0f / 6,
            -0.5f, -0.5f,  0.5f,  1.0f / 6, 0.0f,  2.0f / 6, // Back

            -0.5f,  0.5f,  0.5f,  0.0f / 6, 1.0f, 3.0f / 6,
            -0.5f,  0.5f, -0.5f,  1.0f / 6, 1.0f, 3.0f / 6,
            -0.5f, -0.5f, -0.5f,  1.0f / 6, 0.0f, 3.0f / 6,
            -0.5f, -0.5f, -0.5f,  1.0f / 6, 0.0f, 3.0f / 6,
            -0.5f, -0.5f,  0.5f,  0.0f / 6, 0.0f, 3.0f / 6,
            -0.5f,  0.5f,  0.5f,  0.0f / 6, 1.0f, 3.0f / 6, // Left

            0.5f,  0.5f, -0.5f,  0.0f / 6, 1.0f, 1.0f / 6,
            0.5f,  0.5f,  0.5f,  1.0f / 6, 1.0f, 1.0f / 6,
            0.5f, -0.5f, -0.5f,  0.0f / 6, 0.0f, 1.0f / 6,
            0.5f, -0.5f,  0.5f,  1.0f / 6, 0.0f, 1.0f / 6,
            0.5f, -0.5f, -0.5f,  0.0f / 6, 0.0f, 1.0f / 6,
            0.5f,  0.5f,  0.5f,  1.0f / 6, 1.0f, 1.0f / 6, // Right

            -0.5f, -0.5f, -0.5f,  0.0f / 6, 1.0f, 5.0 / 6,
            0.5f, -0.5f, -0.5f,  1.0f / 6, 1.0f, 5.0 / 6,
            0.5f, -0.5f,  0.5f,  1.0f / 6, 0.0f, 5.0 / 6,
            0.5f, -0.5f,  0.5f,  1.0f / 6, 0.0f, 5.0 / 6,
            -0.5f, -0.5f,  0.5f,  0.0f / 6, 0.0f, 5.0 / 6,
            -0.5f, -0.5f, -0.5f,  0.0f / 6, 1.0f, 5.0 / 6, // Bottom

            0.5f,  0.5f, -0.5f,  1.0f / 6, 1.0f, 4.0f / 6,
            -0.5f,  0.5f, -0.5f,  0.0f / 6, 1.0f, 4.0f / 6,
            0.5f,  0.5f,  0.5f,  1.0f / 6, 0.0f, 4.0f / 6,
            -0.5f,  0.5f,  0.5f,  0.0f / 6, 0.0f, 4.0f / 6,
            0.5f,  0.5f,  0.5f,  1.0f / 6, 0.0f, 4.0f / 6,
            -0.5f,  0.5f, -0.5f,  0.0f / 6, 1.0f, 4.0f / 6 // Top
    };
private:
    Uptr<Shader> shader;
    unsigned int VAO;
    int modelLoc;
    int viewLoc;
    int projLoc;
public:
    explicit BlockRenderer();
    ~BlockRenderer() = default;

    void renderAll(Sptr<Texture> texture, std::vector<glm::vec3> locs, glm::mat4 view, glm::mat4 proj);
};


#endif //GLFW2_BLOCKRENDERER_H
