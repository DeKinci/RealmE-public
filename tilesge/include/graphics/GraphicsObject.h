//
// Created by DeKinci on 12/6/2020.
//

#ifndef TILESGE_GRAPHICSOBJECT_H
#define TILESGE_GRAPHICSOBJECT_H

#include "graphics/Camera.h"
#include "graphics/Shader.h"
#include "graphics/Model.h"
#include "graphics/Texture.h"

class GraphicsObject {
public:
    GraphicsObject(Model &model, Texture *texture);

    GraphicsObject(Model &model);

    void showAt(Camera &camera, const glm::mat4 &transformation);

private:
    Model &model;
    Texture *texture;
};


#endif //TILESGE_GRAPHICSOBJECT_H
