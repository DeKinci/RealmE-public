//
// Created by DeKinci on 5/9/2020.
//

#include "utils/Args.h"

Args::Args(int argc, char **argv) {
    CLI::App app{"Shitty game engine"};

    app.set_help_flag("--help", "Heeeeeeelp");
    app.add_flag("--debug", debug, "Debug mode");
    app.add_option("-l", logfile , "File to log to");
    app.add_option("-w", width, "Windows width");
    app.add_option("-h", height, "Windows height");

    app.parse(argc, argv);
}

bool Args::isDebug() const {
    return debug;
}

const std::string &Args::getLogfile() const {
    return logfile;
}

size_t Args::getWidth() const {
    return width;
}

size_t Args::getHeight() const {
    return height;
}
