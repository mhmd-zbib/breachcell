#include "render/projectile_renderer.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/core_render_system.h"
#include <SDL2/SDL.h>
ProjectileRenderer &ProjectileRenderer::getInstance()
{
  static ProjectileRenderer instance;
  return instance;
}
void ProjectileRenderer::render()
{
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    ProjectileComponent *projectile = entityManager.getProjectileComponent(entityId);
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    if (!projectile || !transform)
      continue;
    int centerX = static_cast<int>(transform->positionX);
    int centerY = static_cast<int>(transform->positionY);
    int radius = 4;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int w = 0; w < radius * 2; w++)
    {
      for (int h = 0; h < radius * 2; h++)
      {
        int dx = radius - w;
        int dy = radius - h;
        if (dx * dx + dy * dy <= radius * radius)
        {
          SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
        }
      }
    }
  }
}
