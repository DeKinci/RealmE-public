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

private:
    bool debug = false;
    std::string logfile = "log.log";
};


#endif //TILESGE_ARGS_H
