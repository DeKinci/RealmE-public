//
// Created by DeKinci on 8/4/2020.
//

#ifndef TILESGE_GAME_OBJECT_H
#define TILESGE_GAME_OBJECT_H

#include "physics/Body.h"
#include "graphics/Model.h"
#include "graphics/Texture.h"
#include "graphics/GraphicsObject.h"

class GameObject {
public:
    GameObject(Body *body, Shader* shader, Model *model, Texture *texture);

    Body *getBody() const;

    void setBody(Body *body);

    void show(Camera &camera) const;

private:
    Body* body;
    Model* model;
    Texture *texture;
    Shader *shader;
};


#endif //TILESGE_GAME_OBJECT_H
