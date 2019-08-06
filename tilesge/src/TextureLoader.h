//
// Created by DeKinci on 8/6/2019.
//

#ifndef TILESGE_TEXTURELOADER_H
#define TILESGE_TEXTURELOADER_H

#include <vector>

struct Texture {
    std::vector<unsigned char> *image;
    double u2;
    double v2;
    double u3;
    double v3;
};

Texture *load();

#endif //TILESGE_TEXTURELOADER_H
