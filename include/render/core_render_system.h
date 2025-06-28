#pragma once
#include <cstdint>
#include <SDL2/SDL.h>
class CoreRenderSystem
{
public:
  static CoreRenderSystem &getInstance();
  void renderAll();
  void setRenderer(SDL_Renderer *renderer);
  SDL_Renderer *getRenderer() const;

private:
  CoreRenderSystem();
  SDL_Renderer *sdlRenderer;
};
