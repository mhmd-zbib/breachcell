#include <SDL2/SDL.h>
#include "render/core_render_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/wall_renderer.h"
#include <cstdint>
WallRenderer &WallRenderer::getInstance()
{
  static WallRenderer instance;
  return instance;
}
void WallRenderer::render()
{
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    SpriteComponent *sprite = entityManager.getSpriteComponent(entityId);
    if (!sprite || sprite->textureId != 0)
      continue;
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    if (!transform)
      continue;
    SDL_Rect wallRect;
    wallRect.x = static_cast<int>(transform->positionX);
    wallRect.y = static_cast<int>(transform->positionY);
    wallRect.w = 32;
    wallRect.h = 32;
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &wallRect);
  }
}
