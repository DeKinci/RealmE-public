//
// Created by DeKinci on 12/6/2020.
//

#include "graphics/GraphicsObject.h"

GraphicsObject::GraphicsObject(Model &model, Texture *texture) : model(model), texture(texture) {}

void GraphicsObject::showAt(Camera &camera, const glm::mat4 &transformation) {
    model.use();

    if (texture != nullptr)
        texture->bind();

    model.showAt(camera, transformation);
}

GraphicsObject::GraphicsObject(Model &model) : model(model) {
    texture = nullptr;
}
