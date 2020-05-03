//
// Created by DeKinci on 5/3/2020.
//

#ifndef TILESGE_BODY_H
#define TILESGE_BODY_H

#include "Model.h"

class Body {
public:
    Body(Model &model, const glm::vec3 &position);

    void setPosition(const glm::vec3 &position);

    void setVelocity(const glm::vec3 &velocity);

    void setAcceleration(const glm::vec3 &acceleration);

    void addPosition(const glm::vec3 &delta);

    void addVelocity(const glm::vec3 &delta);

    void addAcceleration(const glm::vec3 &delta);

    const glm::vec3 &getPosition() const;

    const glm::vec3 &getVelocity() const;

    const glm::vec3 &getAcceleration() const;

    void show(Camera &camera);

private:
    Model& model;
    glm::vec3 position{glm::vec3(0, 0, 0)};
    glm::vec3 velocity{glm::vec3(0, 0, 0)};
    glm::vec3 acceleration{glm::vec3(0, 0, 0)};
};


#endif //TILESGE_BODY_H
