#include "engine/engine.h"
#include "game/game.h"

int main()
{
    WindowConfig config;
    config.title = "Phantom Breach";
    config.width = 1280;
    config.height = 720;
    config.fullscreen = true;
    Game game;
    Engine engine(&game, config);
    engine.initialize();
    engine.run();
    engine.shutdown();
    return 0;
}
