#include "render/wall_renderer.h"
#include "core/camera_service.h"
#include "ecs/components.h"
#include "ecs/entity_manager.h"
#include "render/core_render_system.h"
#include <SDL2/SDL.h>

WallRenderer::WallRenderer(EntityManager* entityManagerPointer, CameraService* cameraServicePointer,
                           CoreRenderSystem* coreRenderSystemPointer) :
    entityManager(entityManagerPointer),
    cameraService(cameraServicePointer),
    coreRenderSystem(coreRenderSystemPointer) {
}

void WallRenderer::render() {
  SDL_Renderer* renderer   = coreRenderSystem->getRenderer();
  SDL_Rect      cameraView = cameraService->getViewRectangle();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId) {
    TransformComponent* transform = entityManager->getTransformComponent(entityId);
    SpriteComponent*    sprite    = entityManager->getSpriteComponent(entityId);
    if (!transform || !sprite) {
      continue;
    }
    if (sprite->textureId != 2) {
      continue;
    }
    float    centerX = transform->positionX - cameraView.x;
    float    centerY = transform->positionY - cameraView.y;
    int      width   = 64;
    int      height  = 64;
    SDL_Rect dstRect;
    dstRect.x = static_cast<int>(centerX - width * 0.5f);
    dstRect.y = static_cast<int>(centerY - height * 0.5f);
    dstRect.w = width;
    dstRect.h = height;
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &dstRect);
  }
}
