#ifndef ENGINE_H
#define ENGINE_H

#include "../game/game.h"
#include "core/igame.h"
#include "ecs/systems/camera_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/velocity_system.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include "input/input_system.h"
#include "resources/texture_manager.h"
#include "utils/timer.h"
#include <memory>

class Engine
{
  public:
    Engine(const WindowConfig& config);
    void initialize();
    void run();
    void render();
    void shutdown();
    void processInput();
    void processUpdate();
    void processRender();

  private:
    bool isRunning;
    WindowConfig windowConfig;
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputSystem> inputSystem;
    std::unique_ptr<Timer> timer;
    std::shared_ptr<MovementSystem> movementSystem;
    std::shared_ptr<VelocitySystem> velocitySystem;
    std::shared_ptr<CameraSystem> cameraSystem;
    std::unique_ptr<TextureManager> textureManager;
    std::unique_ptr<Game> gameInstance;
};

#endif
