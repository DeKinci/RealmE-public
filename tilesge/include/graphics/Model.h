#ifndef TILESGE_MODEL_H
#define TILESGE_MODEL_H

#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"

class Model {
public:
    Model(Mesh &mesh, Shader &shader);
    ~Model();

    void use() const;

    void showAt(Camera &camera, const glm::mat4 &transformation) const;

    Shader &shader;
private:
    GLuint id;
    GLuint bufferId;

    Mesh &mesh;
};

#endif //TILESGE_MODEL_H
