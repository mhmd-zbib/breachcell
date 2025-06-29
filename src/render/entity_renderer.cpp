#include "render/entity_renderer.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/texture_manager.h"
#include "render/core_render_system.h"
#include "core/camera_service.h"
#include <SDL2/SDL.h>
EntityRenderer &EntityRenderer::getInstance()
{
  static EntityRenderer instance;
  return instance;
}
void EntityRenderer::render()
{
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  SDL_Rect cameraView = CameraService::getInstance().getViewRectangle();
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    SpriteComponent *sprite = entityManager.getSpriteComponent(entityId);
    CollisionComponent *collision = entityManager.getCollisionComponent(entityId);
    if (!transform || !sprite)
      continue;
    SDL_Texture *texture = TextureManager::getInstance().getTexture(sprite->textureId);
    if (!texture)
      continue;
    float centerX = transform->positionX + (collision ? collision->offsetX : 0.0f) - cameraView.x;
    float centerY = transform->positionY + (collision ? collision->offsetY : 0.0f) - cameraView.y;
    int width = 64;
    int height = 64;
    if (collision)
    {
      width = static_cast<int>(collision->boxWidth);
      height = static_cast<int>(collision->boxHeight);
    }
    SDL_Rect dstRect;
    dstRect.x = static_cast<int>(centerX - width * 0.5f);
    dstRect.y = static_cast<int>(centerY - height * 0.5f);
    dstRect.w = width;
    dstRect.h = height;
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    float crossCenterX = centerX;
    float crossCenterY = centerY;
    float crossSize = 16.0f;
    SDL_Color crossColor = {255, 0, 0, 255};
    renderCross(renderer, crossCenterX, crossCenterY, crossSize, crossColor);
  }
}

void EntityRenderer::renderCross(SDL_Renderer *rendererPointer, float centerX, float centerY, float crossSize, SDL_Color crossColor)
{
  if (!rendererPointer)
    throw std::invalid_argument("rendererPointer is null");
  SDL_SetRenderDrawColor(rendererPointer, crossColor.r, crossColor.g, crossColor.b, crossColor.a);
  int halfSize = static_cast<int>(crossSize * 0.5f);
  int cx = static_cast<int>(centerX);
  int cy = static_cast<int>(centerY);
  SDL_RenderDrawLine(rendererPointer, cx - halfSize, cy, cx + halfSize, cy);
  SDL_RenderDrawLine(rendererPointer, cx, cy - halfSize, cx, cy + halfSize);
}
