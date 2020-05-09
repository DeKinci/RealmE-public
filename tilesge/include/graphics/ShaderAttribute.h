//
// Created by DeKinci on 8/13/2019.
//

#ifndef TILESGE_SHADERATTRIBUTE_H
#define TILESGE_SHADERATTRIBUTE_H

#include <cstddef>

class ShaderAttribute {
public:
    ShaderAttribute(const char *name, size_t size, size_t position) :
            name{name},
            size{size},
            position{position} {
    }

    const char *name;
    size_t size;
    size_t position;
};


#endif //TILESGE_SHADERATTRIBUTE_H
