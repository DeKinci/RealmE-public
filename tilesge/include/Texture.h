#ifndef TILESGE_TEXTURE_H
#define TILESGE_TEXTURE_H

#include <glad/glad.h>
#include <TextureLoader.h>

class Texture {
public:
    GLuint ID;

    Texture(const GLchar *name, GLuint magFilter, GLuint activeTexture = GL_TEXTURE0);
    void bind() const;
};


#endif //TILESGE_TEXTURE_H
