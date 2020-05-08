#include "utils/Args.h"
#include "GameApp.h"

int main(int argc, char **argv) {
    auto args = new Args(argc, argv);
    auto app = new GameApp(args);
    app->run();
    return 0;
}
