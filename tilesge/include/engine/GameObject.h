//
// Created by DeKinci on 8/4/2020.
//

#ifndef TILESGE_GAME_OBJECT_H
#define TILESGE_GAME_OBJECT_H

#include "physics/Body.h"
#include "graphics/Model.h"

class GameObject {
public:
    GameObject(Body *body, Model *model);

    void setBody(Body *body);

    Body *getBody() const;

    void show(Camera &camera) const;

private:
    Body* body;
    Model* model;
};


#endif //TILESGE_GAME_OBJECT_H
