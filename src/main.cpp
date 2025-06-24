#include <SDL2/SDL.h>
#include <iostream>
#include "core/engine.h"
#include "input/input_handler.h"
#include "render/renderer.h"

int main()
{
  InputHandler &inputHandler = InputHandler::getInstance();
  Renderer &renderer = Renderer::getInstance();
  Engine &engine = Engine::getInstance(inputHandler, renderer);

  if (!engine.init("BreachCell 2D Game", 800, 600))
  {
    return 1;
  }
  while (engine.isRunning())
  {
    engine.handleInput();
    engine.update();
    engine.render();
  }
  engine.clean();
  return 0;
}
