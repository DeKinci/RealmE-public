#ifndef TILESGE_TEXTURELOADER_H
#define TILESGE_TEXTURELOADER_H

#include <glad/glad.h>

struct TextureData {
    GLubyte *image;
    double width;
    double height;
};

TextureData *load(const char * textureName);

#endif //TILESGE_TEXTURELOADER_H
