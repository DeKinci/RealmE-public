#include "utils/Args.h"
#include "game/CubeGameApp.h"

int main(int argc, char **argv) {
    auto args = new Args(argc, argv);
    auto app = new CubeGameApp(args);
    app->run();
    return 0;
}
