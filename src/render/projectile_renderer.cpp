#include "render/projectile_renderer.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/core_render_system.h"
#include "core/camera_service.h"
#include <SDL2/SDL.h>

ProjectileRenderer& ProjectileRenderer::getInstance()
{
  static ProjectileRenderer instance;
  return instance;
}

void ProjectileRenderer::render()
{
  SDL_Renderer* renderer = CoreRenderSystem::getInstance().getRenderer();
  SDL_Rect cameraView = CameraService::getInstance().getViewRectangle();
  EntityManager& entityManager = EntityManager::getInstance();

  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    ProjectileComponent* projectile = entityManager.getProjectileComponent(entityId);
    TransformComponent* transform = entityManager.getTransformComponent(entityId);

    if (!projectile || !transform)
    {
      continue;
    }

    float centerX = transform->positionX - cameraView.x;
    float centerY = transform->positionY - cameraView.y;
    int radius = 1;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int w = -radius; w <= radius; w++)
    {
      for (int h = -radius; h <= radius; h++)
      {
        if (w * w + h * h <= radius * radius)
        {
          SDL_RenderDrawPoint(renderer, static_cast<int>(centerX) + w, static_cast<int>(centerY) + h);
        }
      }
    }
  }
}
