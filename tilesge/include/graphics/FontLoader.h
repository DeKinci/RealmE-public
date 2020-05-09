//
// Created by DeKinci on 5/3/2020.
//

#ifndef TILESGE_FONTLOADER_H
#define TILESGE_FONTLOADER_H

#include "Font.h"

class FontLoader {
public:
    static Font &load(const char *fontName);
};


#endif //TILESGE_FONTLOADER_H
