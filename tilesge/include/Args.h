//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_ARGS_H
#define TILESGE_ARGS_H

#include <string>
#include "CLI11.hpp"

class Args {
public:
    Args(int argc, char **argv);

    bool isDebug() const;

    const std::string &getLogfile() const;

    size_t getWidth() const;

    size_t getHeight() const;

private:
    bool debug = false;
    std::string logfile = "log.log";
    size_t width = 640;
    size_t height = 480;
};


#endif //TILESGE_ARGS_H
