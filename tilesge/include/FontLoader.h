//
// Created by DeKinci on 5/3/2020.
//

#ifndef FREETYPE_FONTLOADER_H
#define FREETYPE_FONTLOADER_H

#include <cmrc/cmrc.hpp>
#include <glad/glad.h>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Font.h"

class FontLoader {
public:
    static Font &load(std::string fontName);
};


#endif //FREETYPE_FONTLOADER_H
