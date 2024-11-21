//
// Created by kgil2 on 9/20/2024.
//

#include "FontRenderer.h"

#include <utility>


FontRenderer::FontRenderer(){
    if (FT_Init_FreeType(&lib)) {
        util::log(util::LogLevel::ERROR, "Could not load FreeType library!");
        exit(-1);
    }
    isLibLoaded = true;

    shader = std::make_unique<Shader>(FontRenderer::vertPath, FontRenderer::fragPath);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // We will constantly update this based on each character
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader->use();
    colorLoc = shader->getLoc("inColor");
    modelLoc = shader->getLoc( "model");
    viewLoc = shader->getLoc("view");
    projLoc = shader->getLoc("projection");
    shader->setInt("texture0", 0);
}

void FontRenderer::addFont(const std::string& path, const std::string& alias) {
    if(!isLibLoaded) {
        util::log(util::LogLevel::EXCEPTION, "Attempting to load font while lib is unloaded!");
        exit(-1);
    }
    // Load font
    FT_Face face;
    if(FT_New_Face(lib, path.c_str(), 0, &face)) {
        util::log(util::LogLevel::ERROR, "Could not load font named: " + path);
        exit(-1);
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    charMap.insert(std::pair(alias, std::make_shared<std::map<char, Character>>()));

    // Iterate through each ASCII character
    for(unsigned char c = 0; c < 128; c++) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            util::log(util::LogLevel::ERROR, "Failed to load character from font: " + path);
            exit(-1);
        }

        // Load texture from glyph into GPU
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // Optimal parameters for fonts blah blah
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
        };

        // Insert into char map
        charMap[alias]->insert(std::pair(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Deallocate
    FT_Done_Face(face);
}

void FontRenderer::unloadLib() {
    FT_Done_FreeType(lib);
    isLibLoaded = false;
}

void FontRenderer::renderFlatString(const std::string& font, std::string s, glm::vec2 pos, float size,
                                    glm::vec3 color, glm::ivec2 screenSize) {
    auto identMat = glm::value_ptr(glm::mat4(1.0f));
    auto ortho = glm::ortho(0.0f, static_cast<float>(screenSize.x),
                            0.0f, static_cast<float>(screenSize.y));
    shader->use();
    glUniform3f(colorLoc, color.x, color.y, color.z);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,identMat);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, identMat);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for(c = s.begin(); c != s.end(); c++) {
        Character ch = charMap[font].get()->at(*c);

        float xpos = pos.x + ch.bearing.x * size;
        float ypos = pos.y - (ch.size.y - ch.bearing.y) * size;

        float w = ch.size.x * size;
        float h = ch.size.y * size;

        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        pos.x += (ch.advance >> 6) * size;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int FontRenderer::getStringSize(const std::string& font, const std::string& s, float size) {
    std::string::const_iterator c;
    int pixelLen = 0;
    for(c = s.begin(); c != s.end(); c++) {
        pixelLen += (charMap[font].get()->at(*c).advance >> 6) * size;
    }
    return pixelLen;
}