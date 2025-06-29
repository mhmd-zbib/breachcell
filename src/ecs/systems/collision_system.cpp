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
    TransformComponent *transformA = entityManager.getTransformComponent(entityA);
    if (!collisionA || !transformA)
      continue;
    ProjectileComponent *projectileA = entityManager.getProjectileComponent(entityA);
    for (std::uint32_t entityB = entityA + 1; entityB < EntityManager::MAX_ENTITY_ID; ++entityB)
    {
      CollisionComponent *collisionB = entityManager.getCollisionComponent(entityB);
      TransformComponent *transformB = entityManager.getTransformComponent(entityB);
      if (!collisionB || !transformB)
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
      bool overlap =
          collisionA->getMinX(transformA->positionX) < collisionB->getMaxX(transformB->positionX) &&
          collisionA->getMaxX(transformA->positionX) > collisionB->getMinX(transformB->positionX) &&
          collisionA->getMinY(transformA->positionY) < collisionB->getMaxY(transformB->positionY) &&
          collisionA->getMaxY(transformA->positionY) > collisionB->getMinY(transformB->positionY);
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
        float overlapX = (collisionA->getMaxX(transformA->positionX) < collisionB->getMaxX(transformB->positionX) ? collisionA->getMaxX(transformA->positionX) : collisionB->getMaxX(transformB->positionX)) - (collisionA->getMinX(transformA->positionX) > collisionB->getMinX(transformB->positionX) ? collisionA->getMinX(transformA->positionX) : collisionB->getMinX(transformB->positionX));
        float overlapY = (collisionA->getMaxY(transformA->positionY) < collisionB->getMaxY(transformB->positionY) ? collisionA->getMaxY(transformA->positionY) : collisionB->getMaxY(transformB->positionY)) - (collisionA->getMinY(transformA->positionY) > collisionB->getMinY(transformB->positionY) ? collisionA->getMinY(transformA->positionY) : collisionB->getMinY(transformB->positionY));
        if (overlapX < overlapY)
        {
          float centerAX = transformA->positionX + collisionA->offsetX;
          float centerBX = transformB->positionX + collisionB->offsetX;
          if (centerAX < centerBX)
            transformA->positionX -= overlapX * 0.5f;
          else
            transformA->positionX += overlapX * 0.5f;
        }
        else
        {
          float centerAY = transformA->positionY + collisionA->offsetY;
          float centerBY = transformB->positionY + collisionB->offsetY;
          if (centerAY < centerBY)
            transformA->positionY -= overlapY * 0.5f;
          else
            transformA->positionY += overlapY * 0.5f;
        }
      }
    }
  }
}

void CollisionSystem::renderDebug()
{
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  EntityManager &entityManager = EntityManager::getInstance();
  SDL_Rect cameraView = CameraService::getInstance().getViewRectangle();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    CollisionComponent *col = entityManager.getCollisionComponent(entityId);
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    if (!col || !transform)
      continue;
    SDL_Rect rect;
    rect.x = static_cast<int>(col->getMinX(transform->positionX) - cameraView.x);
    rect.y = static_cast<int>(col->getMinY(transform->positionY) - cameraView.y);
    rect.w = static_cast<int>(col->boxWidth);
    rect.h = static_cast<int>(col->boxHeight);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    int centerX = static_cast<int>(transform->positionX + col->offsetX - cameraView.x);
    int centerY = static_cast<int>(transform->positionY + col->offsetY - cameraView.y);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, centerX - 8, centerY, centerX + 8, centerY);
    SDL_RenderDrawLine(renderer, centerX, centerY - 8, centerX, centerY + 8);
  }
}
