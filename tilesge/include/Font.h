//
// Created by DeKinci on 5/3/2020.
//

#ifndef FREETYPE_FONT_H
#define FREETYPE_FONT_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <map>
#include "AppWindow.h"
#include "Shader.h"
#include <string>

struct Symbol {
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Font {
public:
    explicit Font(std::map<char, Symbol> characters);

    void show(AppWindow &window, std::string text, float x, float y);

private:
    std::map<char, Symbol> Characters;
    GLuint vao;
    GLuint vbo;
};


#endif //FREETYPE_FONT_H
