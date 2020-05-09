//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_SHADERS_H
#define TILESGE_SHADERS_H

#include "Shader.h"

namespace Shaders {
    static Shader &basicShader() {
        static Shader shader("vertex", "color");
        return shader;
    }

    static Shader &lightShader() {
        static Shader shader("lightVertex", "lightColor");
        return shader;
    }

    static Shader &fontShader() {
        static Shader shader("fontVertex", "fontColor");
        return shader;
    }
}

#endif //TILESGE_SHADERS_H
