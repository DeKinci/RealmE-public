#include "graphics/Model.h"
#include <glm/gtc/matrix_transform.hpp>

Model::Model(Mesh &mesh, Shader &shader) :
        shader{shader},
        mesh{mesh} {
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);

    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, mesh.verticesSize, mesh.vertices, GL_STATIC_DRAW);
    shader.use();
    for (size_t i = 0; i < mesh.attributesSize; i++) {
        ShaderAttribute *attribute = mesh.attributes[i];
        shader.attrib(attribute->name, attribute->size, GL_FLOAT, GL_FALSE,
                      mesh.attributesLength * sizeof(float),
                      (void *) (attribute->position * sizeof(float)));
    }
}

Model::~Model() {
    delete &mesh;
}

void Model::use() const {
    shader.use();
    glBindVertexArray(id);
}

void Model::showAt(Camera &camera, const glm::mat4 &transformation) const {
    shader.set("projection", camera.getProjection());
    shader.set("view", camera.getView());
    shader.set("model", transformation);
    glDrawArrays(GL_TRIANGLES, 0, mesh.verticesAmount);
}
