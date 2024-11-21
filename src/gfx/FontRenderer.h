//
// Created by kgil2 on 9/20/2024.
//

#ifndef GLFW2_FONTRENDERER_H
#define GLFW2_FONTRENDERER_H

#include <map>
#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "../util.h"

class FontRenderer {
public:
    const static inline std::string vertPath = "../src/shaders/font_v.glsl";
    const static inline std::string fragPath = "../src/shaders/font_f.glsl";

    explicit FontRenderer();
    ~FontRenderer() = default;

    void addFont(const std::string& path, const std::string& alias);
    void unloadLib();
    //void addRenderedText(std::string font, std::string s, glm::vec3 model, glm::vec3 color);
    void renderFlatString(const std::string& font, std::string s, glm::vec2 pos, float size, glm::vec3 color,
                          glm::ivec2 screenSize);
    int getStringSize(const std::string& font, const std::string& s, float size);
private:
    struct Character {
        unsigned int id;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned int advance;
    };

    bool isLibLoaded;
    FT_Library lib;

    unsigned int VAO, VBO;
    int colorLoc;
    int modelLoc;
    int viewLoc;
    int projLoc;

    Uptr<Shader> shader;
    std::map<std::string, Sptr<std::map<char, Character>>> charMap;
};


#endif //GLFW2_FONTRENDERER_H
