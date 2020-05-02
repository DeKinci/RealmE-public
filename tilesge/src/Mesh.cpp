#include "Mesh.h"

Mesh::Mesh(const float *vertices, size_t verticesSize, ShaderAttribute *attributes[], size_t attributesSize) : vertices(
        vertices), verticesSize(verticesSize), attributesSize(attributesSize), attributes(attributes) {
    attributesLength = 0;
    for (size_t i = 0; i < attributesSize; i++) {
        ShaderAttribute* attribute = attributes[i];
        attributesLength += attribute->size;
    }
    verticesAmount = verticesSize / attributesLength;
}
