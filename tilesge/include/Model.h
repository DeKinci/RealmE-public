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
    Model(Mesh &mesh, Shader &shader);
    ~Model();

    void setTexture(const Texture &texture);

    void setPosition(const glm::vec3 &position);

    void show(Camera &camera);

    void use();

    GLuint id;
    GLuint bufferId;
    Shader shader;

private:
    Mesh &mesh;
    glm::vec3 position;
    glm::mat4 posModel;
    bool text = false;
    const Texture *texture;
};

#endif //TILESGE_MODEL_H
