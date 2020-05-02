//
// Created by DeKinci on 5/2/2020.
//

#ifndef TILESGE_TEXTURES_H
#define TILESGE_TEXTURES_H

#include "Texture.h"

class Textures {
public:
    static Texture &doggo() {
        static Texture doggoTexture("doggo", GL_LINEAR, GL_TEXTURE0);
        return doggoTexture;
    }
};


#endif //TILESGE_TEXTURES_H
