#include "core/game_facade.h"
#include <SDL2/SDL.h>

GameFacade::GameFacade(std::shared_ptr<Engine> engineInstance, const std::string& windowTitle,
                       int windowWidth, int windowHeight) :
    engine(std::move(engineInstance)),
    title(windowTitle),
    width(windowWidth),
    height(windowHeight) {
}

int GameFacade::start() {
  if (!engine->initialize(title.c_str(), width, height)) {
    return 1;
  }
  bool running = true;
  while (running) {
    engine->handleInput();
    engine->update();
    engine->render();
    SDL_Delay(16);
  }
  engine->cleanup();
  return 0;
}
