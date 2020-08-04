//
// Created by DeKinci on 8/4/2020.
//

#include "engine/GameObject.h"

GameObject::GameObject(Body *body, Model *model) : body(body), model(model) {}

Body *GameObject::getBody() const {
    return body;
}

void GameObject::setBody(Body *body) {
    GameObject::body = body;
}

void GameObject::show(Camera &camera) const {
    model->show(camera);
}
