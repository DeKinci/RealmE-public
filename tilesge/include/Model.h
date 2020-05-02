#ifndef TILESGE_MODEL_H
#define TILESGE_MODEL_H

#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"
#include "Position.h"

class Model {
public:
    Model(Mesh &mesh, Shader &shader, Position *position = new Position(0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f));
    ~Model();

    void setTexture(const Texture &texture);

    void setPosition(Position *position);

    void draw(Camera &camera);

    void use();

    GLuint id;
    GLuint bufferId;
    Shader shader;

private:
    Mesh &mesh;
    Position *position;
    glm::mat4 posModel;
    bool text = false;
    const Texture *texture;
};

#endif //TILESGE_MODEL_H
