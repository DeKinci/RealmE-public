#include "graphics/TextureLoader.h"

#include <vector>
#include <lodepng.h>
#include <cmrc/cmrc.hpp>
#include "utils/Log.h"

CMRC_DECLARE(textures);

TextureData *load(const char *textureName) {
    auto *image = new std::vector<unsigned char>;
    unsigned int width = 0, height = 0;

    auto fs = cmrc::textures::get_filesystem();

    auto textureResource = fs.open(std::string(textureName) + ".png");
    std::vector<unsigned char> input = std::vector<unsigned char>(textureResource.begin(), textureResource.end());
    unsigned error = lodepng::decode(*image, width, height, input);

    if (error != 0) {
        Log::error("Can not load texture error {}", error);
        throw std::exception();
    }

    char *imgPtr = reinterpret_cast<char *>(image->data());
    unsigned int wInc = width * 4;//width in char
    char *top = nullptr;
    char *bot = nullptr;
    char temp = 0;
    // Flip texture
    for (unsigned int i = 0; i < height / 2; i++) {
        top = imgPtr + i * wInc;
        bot = imgPtr + (height - i - 1) * wInc;
        for (unsigned int j = 0; j < wInc; j++) {
            temp = *top;
            *top = *bot;
            *bot = temp;
            ++top;
            ++bot;
        }
    }

    auto *t = new TextureData;
    t->image = reinterpret_cast<GLubyte *>(image->data());
    t->width = width;
    t->height = height;

    return t;
}