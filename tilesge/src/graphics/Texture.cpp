#include "graphics/Texture.h"
#include "graphics/TextureLoader.h"

Texture::Texture(const char *name, const GLuint magFilter, GLuint activeTexture) {
    glActiveTexture(activeTexture);
    GLuint texture;
    glGenTextures(1, &texture);
    this->ID = texture;
    this->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    TextureData *tex = load(name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->image);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete tex->image;
    tex->image = nullptr;
    delete tex;
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
