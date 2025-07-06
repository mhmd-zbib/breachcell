#ifndef ENGINE_H
#define ENGINE_H

#include "core/igame.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include "input/input_system.h"
#include "utils/timer.h"
#include <memory>

class Engine
{
  public:
    Engine(IGame* gameInstance, const WindowConfig& config);
    void initialize();
    void run();
    void render();
    void shutdown();
    void processInput();
    void processUpdate();
    void processRender();

  private:
    bool isRunning;
    IGame* game;
    WindowConfig windowConfig;
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputSystem> inputSystem;
    std::unique_ptr<Timer> timer;
};

#endif
