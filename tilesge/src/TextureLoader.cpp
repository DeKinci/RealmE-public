#include "TextureLoader.h"

CMRC_DECLARE(textures);

TextureData *load(const GLchar *textureName) {
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

    char *imgPtr = reinterpret_cast<char *>(image->data());
    unsigned int wInc = width * 4;//width in char
    char *top = nullptr;
    char *bot = nullptr;
    char temp = 0;
    /*flip texture*/
    for (unsigned int i = 0; i < height / 2; i++) {
        top = imgPtr + i * wInc;
        bot = imgPtr + (height - i - 1) * wInc;
        for (unsigned int j = 0; j < wInc; j++) {
            // Swap the chars around.
            temp = *top;
            *top = *bot;
            *bot = temp;
            ++top;
            ++bot;
        }
    }

    auto *t = new TextureData;
    t->image = reinterpret_cast<char *>(image->data());
    t->width = width;
    t->height = height;

    return t;
}