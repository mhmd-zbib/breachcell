#pragma once
#include <SDL2/SDL.h>

class Renderer
{
public:
  static Renderer &getInstance();
  void renderFrame();
  bool init(SDL_Window *window);
  void handleInput(bool &running);

private:
  Renderer();
  ~Renderer();
  void clear();
  void present();
  SDL_Renderer *getSDLRenderer() const;

  SDL_Renderer *renderer;
};
