//
// Created by DeKinci on 8/6/2019.
//

#ifndef TILESGE_SHADERLOADER_H
#define TILESGE_SHADERLOADER_H

#include <glad/glad.h>
#include <cmrc/cmrc.hpp>
#include <vector>
#include <map>
#include <string>

class ShaderLoader {
public:
    static GLuint loadShaders(const char *vertexShaderResource, const char *fragmentShaderResource);
private:
    std::map<std::string, GLuint> map;
};



#endif //TILESGE_SHADERLOADER_H
