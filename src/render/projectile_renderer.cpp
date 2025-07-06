#include "render/projectile_renderer.h"
#include "core/camera_service.h"
#include "ecs/components.h"
#include "ecs/entity_manager.h"
#include "render/core_render_system.h"
#include <SDL2/SDL.h>

ProjectileRenderer::ProjectileRenderer(EntityManager*    entityManagerPointer,
                                       CameraService*    cameraServicePointer,
                                       CoreRenderSystem* coreRenderSystemPointer) :
    entityManager(entityManagerPointer),
    cameraService(cameraServicePointer),
    coreRenderSystem(coreRenderSystemPointer) {
}

void ProjectileRenderer::render() {
  SDL_Renderer* renderer   = coreRenderSystem->getRenderer();
  SDL_Rect      cameraView = cameraService->getViewRectangle();

  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId) {
    ProjectileComponent* projectile = entityManager->getProjectileComponent(entityId);
    TransformComponent*  transform  = entityManager->getTransformComponent(entityId);

    if (!projectile || !transform) {
      continue;
    }

    float centerX = transform->positionX - cameraView.x;
    float centerY = transform->positionY - cameraView.y;
    int   radius  = 1;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int w = -radius; w <= radius; w++) {
      for (int h = -radius; h <= radius; h++) {
        if (w * w + h * h <= radius * radius) {
          SDL_RenderDrawPoint(renderer, static_cast<int>(centerX) + w,
                              static_cast<int>(centerY) + h);
        }
      }
    }
  }
}
