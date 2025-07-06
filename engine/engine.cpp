#include "engine.h"
#include "../game/game.h"
#include "core/igame.h"
#include "ecs/entity_manager.h"
#include "ecs/systems/camera_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/render_system.h"
#include "ecs/systems/velocity_system.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include "input/input_system.h"
#include "utils/timer.h"
#include <cassert>
#include <memory>
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
    renderSystem = std::make_shared<RenderSystem>();
    renderSystem->setCameraSystem(cameraSystem);
    renderer->setCameraSystem(cameraSystem);
    if (cameraSystem)
        cameraSystem->setViewportSize(static_cast<float>(windowConfig.width), static_cast<float>(windowConfig.height));
    isRunning = true;
    if (game)
    {
        game->initialize();
        int playerId = game->getPlayerEntityId();
        cameraSystem->setTargetEntity(playerId);
    }
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
    EntityManager* entityManager = nullptr;
    int playerEntityId = 0;
    if (game)
    {
        entityManager = &(game->getEntityManager());
        playerEntityId = game->getPlayerEntityId();
    }
    inputSystem->nextFrame();
    if (movementSystem && entityManager)
        movementSystem->update(inputSystem.get(), playerEntityId, *entityManager, deltaTime);
    if (cameraSystem && entityManager)
        cameraSystem->update(*entityManager, deltaTime);
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
        EntityManager* entityManager = nullptr;
        if (game)
            entityManager = &(game->getEntityManager());
        if (renderSystem && entityManager)
            renderSystem->render(*entityManager, renderer.get());
        renderer->present();
    }
}

void Engine::shutdown()
{
    isRunning = false;
    if (game)
        game->shutdown();
    renderer.reset();
    window.reset();
    inputSystem.reset();
    timer.reset();
    movementSystem.reset();
    velocitySystem.reset();
    cameraSystem.reset();
    renderSystem.reset();
}
