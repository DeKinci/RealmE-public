//
// Created by DeKinci on 5/3/2020.
//

#ifndef TILESGE_FONTLOADER_H
#define TILESGE_FONTLOADER_H

#include <cmrc/cmrc.hpp>
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Font.h"
#include "utils/Log.h"

class FontLoader {
public:
    static Font &load(std::string fontName);
};


#endif //TILESGE_FONTLOADER_H