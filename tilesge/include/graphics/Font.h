//
// Created by DeKinci on 5/3/2020.
//

#ifndef TILESGE_FONT_H
#define TILESGE_FONT_H

#include <glad/glad.h>
#include <map>
#include <string>

#include "Projector.h"

struct Symbol {
    GLuint textureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class Font {
public:
    explicit Font(std::map<char, Symbol> characters);

    void show(Projector *projector, const char *text, float x, float y);

private:
    std::map<char, Symbol> Characters;
    GLuint vao;
    GLuint vbo;
};


#endif //TILESGE_FONT_H
