#include "engine/engine.h"
#include "engine/graphics/window.h"

int main()
{
    WindowConfig config;
    config.title = "Phantom Breach";
    config.width = 1280;
    config.height = 720;
    config.fullscreen = true;

    Engine engine(config);
    engine.initialize();
    engine.run();
    engine.shutdown();
    return 0;
}
