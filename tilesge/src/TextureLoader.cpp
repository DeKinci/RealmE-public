#include "TextureLoader.h"

CMRC_DECLARE(textures);

TextureData *load(const GLchar * textureName) {
    auto *image = new std::vector<unsigned char>;
    unsigned int width = 0, height = 0;

    auto fs = cmrc::textures::get_filesystem();

    auto textureResource = fs.open(std::string(textureName) + ".png");
    std::vector<unsigned char> input = std::vector<unsigned char>(textureResource.begin(), textureResource.end());
    unsigned error = lodepng::decode(*image, width, height, input);

    // If there's an error, display it.
    if (error != 0) {
        throw std::exception();
    }

    auto *t = new TextureData;
    t->image = reinterpret_cast<char *>(image->data());
    t->width = width;
    t->height = height;

    return t;
}