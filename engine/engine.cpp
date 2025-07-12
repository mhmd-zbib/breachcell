#include "engine.h"
#include "../game/game.h"
#include "core/igame.h"
#include "ecs/entity_manager.h"
#include "ecs/systems/camera_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/velocity_system.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include "input/input_system.h"
#include "utils/timer.h"
#include <cassert>
#include <memory>
#include <stdexcept>

Engine::Engine(const WindowConfig& config) : isRunning(false), windowConfig(config) {}

void Engine::initialize()
{
    window = std::make_unique<Window>();
    if (!window->initialize(windowConfig))
        throw std::runtime_error("Window initialization failed");
    renderer = std::make_unique<Renderer>(window.get());
    if (!renderer->initialize())
        throw std::runtime_error("Renderer initialization failed");
    textureManager = std::make_unique<TextureManager>(renderer->getSDLRenderer());
    gameInstance = std::make_unique<Game>(renderer.get(), textureManager.get());
    inputSystem = std::make_unique<InputSystem>();
    timer = std::make_unique<Timer>();
    movementSystem = std::make_shared<MovementSystem>();
    velocitySystem = std::make_shared<VelocitySystem>();
    cameraSystem = std::make_shared<CameraSystem>();
    renderer->setCameraSystem(cameraSystem);
    if (cameraSystem)
        cameraSystem->setViewportSize(static_cast<float>(windowConfig.width), static_cast<float>(windowConfig.height));
    isRunning = true;
    if (gameInstance)
    {
        gameInstance->setRenderer(renderer.get());
        gameInstance->initialize();
        int playerId = gameInstance->getPlayerEntityId();
        cameraSystem->setTargetEntity(playerId);
    }
}

void Engine::run()
{
    assert(window);
    assert(renderer);
    assert(inputSystem);
    assert(timer);
    assert(gameInstance);
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
    if (gameInstance)
    {
        entityManager = &(gameInstance->getEntityManager());
        playerEntityId = gameInstance->getPlayerEntityId();
    }
    inputSystem->nextFrame();
    if (movementSystem && entityManager)
        movementSystem->update(inputSystem.get(), playerEntityId, *entityManager, deltaTime);
    if (cameraSystem && entityManager)
        cameraSystem->update(*entityManager, deltaTime);
    gameInstance->update(deltaTime);
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
        if (gameInstance)
            gameInstance->render(renderer.get());
        renderer->present();
    }
}

void Engine::shutdown()
{
    isRunning = false;
    if (gameInstance)
        gameInstance->shutdown();
    renderer.reset();
    window.reset();
    inputSystem.reset();
    timer.reset();
    movementSystem.reset();
    velocitySystem.reset();
    cameraSystem.reset();
}
