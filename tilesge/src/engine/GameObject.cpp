//
// Created by DeKinci on 8/4/2020.
//

#include "engine/GameObject.h"

GameObject::GameObject(Body *body, Shader* shader, Model *model, Texture *texture) : body(body), model(model), texture(texture) {}

Body *GameObject::getBody() const {
    return body;
}

void GameObject::setBody(Body *body) {
    GameObject::body = body;
}

void GameObject::show(Camera &camera) const {
    texture->bind();
    body->show(camera);
}
