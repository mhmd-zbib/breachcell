#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "render/renderer.h"
#include "input/input_handler.h"

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

private:
  Engine(InputHandler &inputHandler, Renderer &renderer);
  InputHandler &inputHandlerReference;
  Renderer &rendererReference;
  SDL_Window *window;
  bool running;
};
