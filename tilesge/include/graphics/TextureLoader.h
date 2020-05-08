#ifndef TILESGE_TEXTURELOADER_H
#define TILESGE_TEXTURELOADER_H

#include <vector>
#include <glad/glad.h>
#include <lodepng.h>
#include <cmrc/cmrc.hpp>

struct TextureData {
    char *image;
    double width;
    double height;
};

TextureData *load(const GLchar * textureName);

#endif //TILESGE_TEXTURELOADER_H
