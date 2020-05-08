//
// Created by DeKinci on 5/9/2020.
//

#include "Args.h"

Args::Args(int argc, char **argv) {
    CLI::App app{"Shitty game engine"};

    app.add_option("-l", logfile , "File to log to");
    app.add_flag("--debug", debug, "Debug mode");

    app.parse(argc, argv);
}

bool Args::isDebug() const {
    return debug;
}

const std::string &Args::getLogfile() const {
    return logfile;
}
