#pragma once
#include <stdexcept>
#include <SDL2/SDL.h>

class EntityRenderer
{
public:
  static EntityRenderer& getInstance();
  void render();
  void renderCross(SDL_Renderer* rendererPointer, float centerX, float centerY, float crossSize,
                   SDL_Color crossColor);

private:
  EntityRenderer() = default;
  EntityRenderer(const EntityRenderer&) = delete;
  EntityRenderer& operator=(const EntityRenderer&) = delete;
};
