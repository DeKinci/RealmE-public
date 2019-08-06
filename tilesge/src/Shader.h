//
// Created by DeKinci on 8/6/2019.
//

#ifndef TILESGE_SHADER_H
#define TILESGE_SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderLoader.h"

class Shader
{
public:
    // the program ID
    GLuint ID;

    // constructor reads and builds the shader
    Shader(const GLchar* vertexName, const GLchar* fragmentName);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};


#endif //TILESGE_SHADER_H
