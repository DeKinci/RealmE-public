#ifndef TILESGE_MESH_H
#define TILESGE_MESH_H

#include "ShaderAttribute.h"

class Mesh {
public:
    Mesh(const float *vertices, size_t verticesSize, ShaderAttribute *attributes[], size_t attributesSize);

    const float *vertices;
    size_t verticesSize;
    ShaderAttribute **attributes;
    size_t attributesSize;
    size_t attributesLength;
    size_t verticesAmount;
};


#endif //TILESGE_MESH_H
