//
// Created by DeKinci on 8/13/2019.
//

#ifndef TILESGE_SHADERATTRIBUTE_H
#define TILESGE_SHADERATTRIBUTE_H

#include <glad/glad.h>


class ShaderAttribute {
public:
    ShaderAttribute(const GLchar *name, GLuint size, GLuint position) : name{name}, size{size}, position{position} {}

    const GLchar * name;
    GLuint size;
    GLuint position;
};


#endif //TILESGE_SHADERATTRIBUTE_H
