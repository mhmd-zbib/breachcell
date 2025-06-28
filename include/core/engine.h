#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <cstdint>
#include "render/renderer.h"
#include "input/input_handler.h"
#include "ecs/systems/input_system.h"

class ShootingSystem;

class Engine
{
public:
  static Engine &getInstance(InputHandler &inputHandler, Renderer &renderer);
  void run();
  bool init(const char *windowTitle, int windowWidth, int windowHeight);
  bool isRunning() const;
  void handleInput();
  void update();
  void render();
  void clean();
  void setPlayerEntityId(std::uint32_t id);
  std::uint32_t getPlayerEntityId() const { return playerEntityId; }

private:
  Engine(InputHandler &inputHandler, Renderer &renderer);
  InputHandler &inputHandlerReference;
  Renderer &rendererReference;
  SDL_Window *window;
  bool running;
  std::uint32_t playerEntityId = 0;
};
