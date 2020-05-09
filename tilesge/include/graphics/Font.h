//
// Created by DeKinci on 5/3/2020.
//

#ifndef TILESGE_FONT_H
#define TILESGE_FONT_H

#include <map>
#include <string>

#include "AppWindow.h"

struct Symbol {
    GLuint textureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class Font {
public:
    explicit Font(std::map<char, Symbol> characters);

    void show(AppWindow &window, const char *text, float x, float y);

private:
    std::map<char, Symbol> Characters;
    GLuint vao;
    GLuint vbo;
};


#endif //TILESGE_FONT_H
