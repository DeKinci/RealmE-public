//
// Created by DeKinci on 8/6/2019.
//

#include <lodepng.h>
#include <cmrc/cmrc.hpp>
#include "TextureLoader.h"

CMRC_DECLARE(textures);

Texture *load() {
    std::vector<unsigned char> image;
    unsigned width, height;

    auto fs = cmrc::textures::get_filesystem();
    auto textureResource = fs.open("doggo.png");
    std::vector<unsigned char> input = std::vector<unsigned char>(textureResource.begin(), textureResource.end());
    unsigned error = lodepng::decode(image, width, height, input);

    // If there's an error, display it.
    if (error != 0) {
        throw std::exception();
    }

    size_t u2 = 1;
    while (u2 < width) u2 *= 2;
    size_t v2 = 1;
    while (v2 < height) v2 *= 2;

    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
    double u3 = (double) width / u2;
    double v3 = (double) height / v2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++)
            for (size_t c = 0; c < 4; c++) {
                image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
            }

    auto *t = new Texture;
    t->image = &image2;
    t->u2 = u2;
    t->v2 = v2;
    t->u3 = u3;
    t->v3 = v3;

    return t;
}