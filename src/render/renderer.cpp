#include "render/renderer.h"
#include <iostream>

Renderer &Renderer::getInstance()
{
  static Renderer instance;
  return instance;
}

Renderer::Renderer() : renderer(nullptr) {}
Renderer::~Renderer()
{
  if (renderer)
  {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
}

bool Renderer::init(SDL_Window *window)
{
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

void Renderer::clear()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Renderer::present()
{
  SDL_RenderPresent(renderer);
}

SDL_Renderer *Renderer::getSDLRenderer() const
{
  return renderer;
}

void Renderer::renderFrame()
{
  clear();
  present();
}
