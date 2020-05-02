#include "Model.h"
#include <iostream>

Model::Model(Mesh &mesh, Shader &shader, Position *position) :
        shader{shader},
        mesh{mesh} {

    setPosition(position);

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    this->id = vertexArrayID;

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.verticesSize, mesh.vertices, GL_STATIC_DRAW);
    bufferId = vertexbuffer;
    shader.use();
    for (size_t i = 0; i < mesh.attributesSize; i++) {
        ShaderAttribute *attribute = mesh.attributes[i];
        shader.attrib(attribute->name, attribute->size, GL_FLOAT, GL_FALSE,
                      mesh.attributesLength * sizeof(float),
                      (void *) (attribute->position * sizeof(float)));
    }

    shader.use();
    glBindVertexArray(id);
}

void Model::setTexture(const Texture &texture) {
    shader.use();
    shader.set("texture", 0);
    this->texture = &texture;
    text = true;
}

void Model::setPosition(Position *position) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position->getCoords());
    model = glm::rotate(model, position->getRotationAngle(), position->getRotation());
    posModel = model;
    this->position = position;
}

void Model::draw(Camera &camera) {
    glBindVertexArray(id);
    shader.use();
    if (text) {
        texture->bind();
    }
    shader.set("projection", camera.getProjection());
    shader.set("view", camera.getView());
    shader.set("model", posModel);
//    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glDrawArrays(GL_TRIANGLES, 0, mesh.verticesAmount);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Model::~Model() {
    delete &mesh;
    delete position;
}

void Model::use() {
    shader.use();
    glBindVertexArray(id);
}
