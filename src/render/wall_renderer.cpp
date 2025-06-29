#include <SDL2/SDL.h>
#include "render/core_render_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/wall_renderer.h"
#include "core/camera_service.h"
#include <cstdint>
WallRenderer &WallRenderer::getInstance()
{
  static WallRenderer instance;
  return instance;
}
void WallRenderer::render()
{
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  SDL_Rect cameraView = CameraService::getInstance().getViewRectangle();
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    SpriteComponent *sprite = entityManager.getSpriteComponent(entityId);
    if (!sprite || sprite->textureId != 0)
      continue;
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    CollisionComponent *collision = entityManager.getCollisionComponent(entityId);
    if (!transform || !collision)
      continue;
    int width = static_cast<int>(collision->boxWidth);
    int height = static_cast<int>(collision->boxHeight);
    SDL_Rect wallRect;
    wallRect.x = static_cast<int>(transform->positionX + collision->offsetX - cameraView.x - width * 0.5f);
    wallRect.y = static_cast<int>(transform->positionY + collision->offsetY - cameraView.y - height * 0.5f);
    wallRect.w = width;
    wallRect.h = height;
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &wallRect);
  }
}
