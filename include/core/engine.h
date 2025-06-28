#pragma once
#include <cstdint>
#include <SDL2/SDL.h>
class Engine
{
public:
  static Engine &getInstance();
  bool init(const char *windowTitle, int windowWidth, int windowHeight);
  void run();
  void clean();
  std::uint32_t getPlayerEntityId() const;

private:
  Engine();
  void handleInput();
  void update();
  void render();
  void createEntities();
  void setPlayerEntityId(std::uint32_t id);
  bool running;
  std::uint32_t playerEntityId = 0;
  class InputHandler *inputHandler;
  class Renderer *renderer;
  SDL_Window *window = nullptr;
};
