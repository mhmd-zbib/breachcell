#include "core/engine.h"
#include "ecs/systems/collision_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/core_render_system.h"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <cmath>

CollisionSystem &CollisionSystem::getInstance()
{
  static CollisionSystem instance;
  return instance;
}

void CollisionSystem::update()
{
  EntityManager &entityManager = EntityManager::getInstance();
  std::uint32_t playerId = Engine::getInstance().getPlayerEntityId();
  for (std::uint32_t entityA = 1; entityA < EntityManager::MAX_ENTITY_ID; ++entityA)
  {
    CollisionComponent *collisionA = entityManager.getCollisionComponent(entityA);
    if (!collisionA)
      continue;
    ProjectileComponent *projectileA = entityManager.getProjectileComponent(entityA);
    for (std::uint32_t entityB = entityA + 1; entityB < EntityManager::MAX_ENTITY_ID; ++entityB)
    {
      CollisionComponent *collisionB = entityManager.getCollisionComponent(entityB);
      if (!collisionB)
        continue;
      ProjectileComponent *projectileB = entityManager.getProjectileComponent(entityB);
      if (projectileA && projectileA->ownerId == playerId && (entityB == playerId))
        continue;
      if (projectileB && projectileB->ownerId == playerId && (entityA == playerId))
        continue;
      if (projectileA && projectileB)
        continue;
      if (projectileA && projectileA->ownerId == entityB)
        continue;
      if (projectileB && projectileB->ownerId == entityA)
        continue;
      if (projectileA && entityB == projectileA->ownerId)
        continue;
      if (projectileB && entityA == projectileB->ownerId)
        continue;
      if ((projectileA && entityB == playerId) || (projectileB && entityA == playerId))
        continue;
      bool overlap = collisionA->intersects(*collisionB);
      if (!overlap)
        continue;
      if (projectileA)
      {
        HealthComponent *healthB = entityManager.getHealthComponent(entityB);
        if (healthB)
          healthB->decrement(1.0f);
        entityManager.destroyEntity(entityA);
        continue;
      }
      if (projectileB)
      {
        HealthComponent *healthA = entityManager.getHealthComponent(entityA);
        if (healthA)
          healthA->decrement(1.0f);
        entityManager.destroyEntity(entityB);
        continue;
      }
      VelocityComponent *velocityA = entityManager.getVelocityComponent(entityA);
      VelocityComponent *velocityB = entityManager.getVelocityComponent(entityB);
      if (velocityA && velocityB)
      {
        float overlapX = (collisionA->getMaxX() < collisionB->getMaxX() ? collisionA->getMaxX() : collisionB->getMaxX()) - (collisionA->getMinX() > collisionB->getMinX() ? collisionA->getMinX() : collisionB->getMinX());
        float overlapY = (collisionA->getMaxY() < collisionB->getMaxY() ? collisionA->getMaxY() : collisionB->getMaxY()) - (collisionA->getMinY() > collisionB->getMinY() ? collisionA->getMinY() : collisionB->getMinY());
        if (overlapX < overlapY)
        {
          if (collisionA->centerX < collisionB->centerX)
          {
            collisionA->centerX -= overlapX * 0.5f;
            collisionB->centerX += overlapX * 0.5f;
          }
          else
          {
            collisionA->centerX += overlapX * 0.5f;
            collisionB->centerX -= overlapX * 0.5f;
          }
        }
        else
        {
          if (collisionA->centerY < collisionB->centerY)
          {
            collisionA->centerY -= overlapY * 0.5f;
            collisionB->centerY += overlapY * 0.5f;
          }
          else
          {
            collisionA->centerY += overlapY * 0.5f;
            collisionB->centerY -= overlapY * 0.5f;
          }
        }
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
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    if (!col || !transform)
      continue;
    SDL_Rect rect;
    rect.x = static_cast<int>(transform->positionX - col->boxWidth * 0.5f);
    rect.y = static_cast<int>(transform->positionY - col->boxHeight * 0.5f);
    rect.w = static_cast<int>(col->boxWidth);
    rect.h = static_cast<int>(col->boxHeight);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    int centerX = static_cast<int>(transform->positionX);
    int centerY = static_cast<int>(transform->positionY);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, centerX - 8, centerY, centerX + 8, centerY);
    SDL_RenderDrawLine(renderer, centerX, centerY - 8, centerX, centerY + 8);
  }
}
