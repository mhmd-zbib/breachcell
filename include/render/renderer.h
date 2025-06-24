#pragma once
#include <SDL2/SDL.h>

class Renderer
{
public:
  static Renderer &getInstance();
  bool init(SDL_Window *window);
  void handleInput(bool &running);
  SDL_Renderer *getSDLRenderer() const;
  void clear();
  void present();

private:
  Renderer();
  ~Renderer();

  SDL_Renderer *renderer;
};
