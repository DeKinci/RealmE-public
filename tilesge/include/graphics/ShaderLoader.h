//
// Created by DeKinci on 8/6/2019.
//

#ifndef TILESGE_SHADERLOADER_H
#define TILESGE_SHADERLOADER_H

#include <glad/glad.h>

class ShaderLoader {
public:
    static GLuint loadShaders(const char *vertexShaderResource, const char *fragmentShaderResource);
};



#endif //TILESGE_SHADERLOADER_H
