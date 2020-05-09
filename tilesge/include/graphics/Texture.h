#ifndef TILESGE_TEXTURE_H
#define TILESGE_TEXTURE_H

#include <glad/glad.h>

class Texture {
public:
    GLuint ID;

    Texture(const char *name, GLuint magFilter, GLuint activeTexture = GL_TEXTURE0);
    void bind() const;
};


#endif //TILESGE_TEXTURE_H
