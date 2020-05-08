//
// Created by DeKinci on 5/1/2020.
//

#ifndef TILESGE_CUBEFORGE_H
#define TILESGE_CUBEFORGE_H

#include "graphics/Model.h"
#include "graphics/Mesh.h"
#include "graphics/Textures.h"
#include "graphics/Shader.h"
#include "physics/Body.h"

class CubeForge {
public:
    static Body* createCube(Texture &texture, int x, int y, int z);
    static Model* createLight(int x, int y, int z);
private:
    static float vertices[180];
    static float lightVertices[180];
};


#endif //TILESGE_CUBEFORGE_H