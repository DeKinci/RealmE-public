//
// Created by DeKinci on 8/6/2019.
//

#ifndef TILESGE_TEXTURE_H
#define TILESGE_TEXTURE_H

#include <glad/glad.h>
#include <TextureLoader.h>

class Texture {
public:
    GLuint ID;

    Texture(const GLchar * name, GLuint magFilter);
    void bind();
};


#endif //TILESGE_TEXTURE_H
