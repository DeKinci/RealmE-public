//
// Created by DeKinci on 5/3/2020.
//

#ifndef FREETYPE_FONT_H
#define FREETYPE_FONT_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <map>
#include "Camera.h"
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

    void show(Camera &camera, std::string text, float x, float y, GLuint VAO, GLuint VBO);

private:
    std::map<char, Symbol> Characters;
};


#endif //FREETYPE_FONT_H
