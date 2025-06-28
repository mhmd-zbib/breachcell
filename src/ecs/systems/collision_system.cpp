#include "ecs/systems/collision_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/core_render_system.h"
#include <SDL2/SDL.h>
#include <stdexcept>
CollisionSystem &CollisionSystem::getInstance()
{
  static CollisionSystem instance;
  return instance;
}
void CollisionSystem::update()
{
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityA = 1; entityA < EntityManager::MAX_ENTITY_ID; ++entityA)
  {
    CollisionComponent *collisionA = entityManager.getCollisionComponent(entityA);
    if (!collisionA)
      continue;
    for (std::uint32_t entityB = entityA + 1; entityB < EntityManager::MAX_ENTITY_ID; ++entityB)
    {
      CollisionComponent *collisionB = entityManager.getCollisionComponent(entityB);
      if (!collisionB)
        continue;
      bool overlap = collisionA->boxX < collisionB->boxX + collisionB->boxWidth &&
                     collisionA->boxX + collisionA->boxWidth > collisionB->boxX &&
                     collisionA->boxY < collisionB->boxY + collisionB->boxHeight &&
                     collisionA->boxY + collisionA->boxHeight > collisionB->boxY;
      if (!overlap)
        continue;
      ProjectileComponent *projectileA = entityManager.getProjectileComponent(entityA);
      ProjectileComponent *projectileB = entityManager.getProjectileComponent(entityB);
      if (projectileA)
      {
        if (projectileA->ownerId == entityB)
          continue;
        HealthComponent *healthB = entityManager.getHealthComponent(entityB);
        if (healthB)
          healthB->decrement(1.0f);
        entityManager.destroyEntity(entityA);
        continue;
      }
      if (projectileB)
      {
        if (projectileB->ownerId == entityA)
          continue;
        HealthComponent *healthA = entityManager.getHealthComponent(entityA);
        if (healthA)
          healthA->decrement(1.0f);
        entityManager.destroyEntity(entityB);
        continue;
      }
    }
  }
}
void CollisionSystem::renderDebug()
{
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    CollisionComponent *col = entityManager.getCollisionComponent(entityId);
    if (!col)
      continue;
    SDL_Rect rect;
    rect.x = static_cast<int>(col->boxX);
    rect.y = static_cast<int>(col->boxY);
    rect.w = static_cast<int>(col->boxWidth);
    rect.h = static_cast<int>(col->boxHeight);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
  }
}
