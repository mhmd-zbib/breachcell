#include "engine.h"
#include "core/igame.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include "input/input_system.h"
#include "utils/timer.h"
#include <cassert>
#include <stdexcept>

Engine::Engine(IGame* gameInstance, const WindowConfig& config)
    : isRunning(false), game(gameInstance), windowConfig(config)
{
}

void Engine::initialize()
{
    window = std::make_unique<Window>();
    if (!window->initialize(windowConfig))
        throw std::runtime_error("Window initialization failed");
    renderer = std::make_unique<Renderer>(window.get());
    if (!renderer->initialize())
        throw std::runtime_error("Renderer initialization failed");
    inputSystem = std::make_unique<InputSystem>();
    timer = std::make_unique<Timer>();
    isRunning = true;
    if (game)
        game->initialize();
}

void Engine::run()
{
    assert(window);
    assert(renderer);
    assert(inputSystem);
    assert(timer);
    assert(game);
    while (isRunning && renderer->isInitialized())
    {
        processInput();
        processUpdate();
        processRender();
    }
}

void Engine::processInput()
{
    inputSystem->pollEvents();
    isRunning = !inputSystem->shouldQuit();
}

void Engine::processUpdate()
{
    float deltaTime = timer->getDeltaTime();
    game->update(deltaTime);
}

void Engine::processRender()
{
    render();
}

void Engine::render()
{
    if (renderer && renderer->isInitialized())
    {
        renderer->clear();
        if (game)
            game->render(renderer.get());
        renderer->present();
    }
}

void Engine::shutdown()
{
    isRunning = false;
    if (game)
        game->shutdown();
    if (renderer)
        renderer->shutdown();
    if (window)
        window->shutdown();
}
