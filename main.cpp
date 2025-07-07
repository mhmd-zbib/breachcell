#include "engine/engine.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/window.h"
#include "engine/resources/texture_manager.h"
#include "game/game.h"

int main()
{
    WindowConfig config;
    config.title = "Phantom Breach";
    config.width = 1280;
    config.height = 720;
    config.fullscreen = true;

    Window window;
    window.initialize(config);

    Renderer renderer(&window);
    renderer.initialize();

    TextureManager textureManager(renderer.getSDLRenderer());

    Game game(&renderer, &textureManager);

    Engine engine(&game, config);
    engine.initialize();
    engine.run();
    engine.shutdown();

    return 0;
}
