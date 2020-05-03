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

    static Texture &leaf() {
        static Texture doggoTexture("leaf", GL_LINEAR, GL_TEXTURE0);
        return doggoTexture;
    }

    static Texture &slab() {
        static Texture doggoTexture("slab", GL_LINEAR, GL_TEXTURE0);
        return doggoTexture;
    }

    static Texture &grass() {
        static Texture doggoTexture("grass", GL_LINEAR, GL_TEXTURE0);
        return doggoTexture;
    }
};


#endif //TILESGE_TEXTURES_H
