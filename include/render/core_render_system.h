#pragma once
#include <cstdint>
#include <SDL2/SDL.h>
class CoreRenderSystem
{
public:
  static CoreRenderSystem &getInstance();
  void renderAll();
  void setRenderer(SDL_Renderer *rendererPointer);
  SDL_Renderer *getRenderer() const;

private:
  CoreRenderSystem();
  CoreRenderSystem(const CoreRenderSystem &) = delete;
  CoreRenderSystem &operator=(const CoreRenderSystem &) = delete;
  SDL_Renderer *sdlRenderer;
};
