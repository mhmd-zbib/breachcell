#pragma once
#include <SDL2/SDL.h>

class Renderer
{
public:
  static Renderer &getInstance();
  bool init(SDL_Window *windowPointer);
  void handleInput(bool &runningFlag);
  SDL_Renderer *getSDLRenderer() const;
  void clear();
  void present();

private:
  Renderer();
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  ~Renderer();

  SDL_Renderer *renderer;
};
