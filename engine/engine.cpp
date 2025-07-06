#include "engine.h"
#include "../game/game.h"
#include "core/igame.h"
#include "graphics/camera.h"
#include "graphics/camera_clamp_strategies.h"
#include "graphics/camera_smoothing_strategies.h"
#include "graphics/camera_tracking_strategies.h"
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
    movementSystem = std::make_shared<MovementSystem>();
    velocitySystem = std::make_shared<VelocitySystem>();
    cameraSystem = std::make_shared<CameraSystem>();
    isRunning = true;
    if (game)
    {
        IInputInjectable* injectable = dynamic_cast<IInputInjectable*>(game);
        if (injectable)
            injectable->setInputSystem(inputSystem.get());
        Game* concreteGame = dynamic_cast<Game*>(game);
        if (concreteGame)
        {
            concreteGame->setMovementSystem(movementSystem);
            concreteGame->setVelocitySystem(velocitySystem);
            concreteGame->setCameraSystem(cameraSystem);
        }
        game->initialize();
    }
    renderer->setCameraSystem(cameraSystem);
    if (cameraSystem)
        cameraSystem->setViewportSize(static_cast<float>(windowConfig.width), static_cast<float>(windowConfig.height));
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
    Game* concreteGame = dynamic_cast<Game*>(game);
    if (cameraSystem && concreteGame)
        cameraSystem->update(concreteGame->getEntityManager(), deltaTime);
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
