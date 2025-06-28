#include "render/entity_renderer.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/texture_manager.h"
#include "render/core_render_system.h"
#include <SDL2/SDL.h>
EntityRenderer &EntityRenderer::getInstance()
{
  static EntityRenderer instance;
  return instance;
}
void EntityRenderer::render()
{
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    SpriteComponent *sprite = entityManager.getSpriteComponent(entityId);
    if (!transform || !sprite)
      continue;
    SDL_Texture *texture = TextureManager::getInstance().getTexture(sprite->textureId);
    if (!texture)
      continue;
    SDL_Rect dstRect;
    dstRect.x = static_cast<int>(transform->positionX);
    dstRect.y = static_cast<int>(transform->positionY);
    dstRect.w = 64;
    dstRect.h = 64;
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
  }
}
