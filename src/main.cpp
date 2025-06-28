#include <SDL2/SDL.h>
#include <iostream>
#include "core/engine.h"

int main()
{
  Engine &engine = Engine::getInstance();
  if (!engine.init("BreachCell 2D Game", 800, 600))
    return 1;
  engine.run();
  engine.clean();
  return 0;
}
