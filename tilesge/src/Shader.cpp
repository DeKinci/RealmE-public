//
// Created by DeKinci on 8/6/2019.
//

#include "Shader.h"

Shader::Shader(const GLchar *vertexName, const GLchar *fragmentName) {
    this->ID = loadShaders(vertexName, fragmentName);
}