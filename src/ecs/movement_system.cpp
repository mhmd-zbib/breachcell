#include "ecs/systems/movement_system.h"
#include "ecs/entity_manager.h"
#include "input/input_handler.h"
#include <cmath>
#include <iostream>

MovementSystem::MovementSystem(EntityManager* entityManagerPtr, InputHandler* inputHandlerPtr) :
    entityManager(entityManagerPtr), inputHandler(inputHandlerPtr) {
}

void MovementSystem::update(float deltaTime, std::uint32_t playerEntityId) {
  if (!entityManager || !inputHandler)
    return;

  auto velocity  = entityManager->getVelocityComponent(playerEntityId);
  auto transform = entityManager->getTransformComponent(playerEntityId);

  if (velocity && transform) {
    velocity->velocityX = 0.0f;
    velocity->velocityY = 0.0f;
    float speed = inputHandler->isKeyPressed(SDLK_LSHIFT) || inputHandler->isKeyPressed(SDLK_RSHIFT)
                      ? SLOW_SPEED
                      : NORMAL_SPEED;
    bool  wKey  = inputHandler->isKeyPressed(SDLK_w);
    bool  wScan = inputHandler->isKeyPressed(SDL_SCANCODE_W);
    bool  sKey  = inputHandler->isKeyPressed(SDLK_s);
    bool  sScan = inputHandler->isKeyPressed(SDL_SCANCODE_S);
    bool  aKey  = inputHandler->isKeyPressed(SDLK_a);
    bool  aScan = inputHandler->isKeyPressed(SDL_SCANCODE_A);
    bool  dKey  = inputHandler->isKeyPressed(SDLK_d);
    bool  dScan = inputHandler->isKeyPressed(SDL_SCANCODE_D);

    if (wKey || wScan) {
      velocity->velocityY = -1.0f;
    }

    if (sKey || sScan) {
      velocity->velocityY = 1.0f;
    }

    if (aKey || aScan) {
      velocity->velocityX = -1.0f;
    }

    if (dKey || dScan) {
      velocity->velocityX = 1.0f;
    }

    float magnitude = std::sqrt(velocity->velocityX * velocity->velocityX +
                                velocity->velocityY * velocity->velocityY);

    if (magnitude > 0.0f) {
      velocity->velocityX = (velocity->velocityX / magnitude) * speed;
      velocity->velocityY = (velocity->velocityY / magnitude) * speed;
    }

    transform->positionX += velocity->velocityX * deltaTime;
    transform->positionY += velocity->velocityY * deltaTime;
  }

  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId) {
    ProjectileComponent* projectile = entityManager->getProjectileComponent(entityId);
    TransformComponent*  transform  = entityManager->getTransformComponent(entityId);
    VelocityComponent*   velocity   = entityManager->getVelocityComponent(entityId);

    if (projectile && transform && velocity) {
      projectile->framesAlive++;
      std::cout << "Projectile entity " << entityId << " framesAlive=" << projectile->framesAlive
                << " position=(" << transform->positionX << ", " << transform->positionY << ")"
                << std::endl;
      float intendedCenterX = transform->positionX + velocity->velocityX * deltaTime;
      float intendedCenterY = transform->positionY + velocity->velocityY * deltaTime;
      transform->positionX  = intendedCenterX;
      transform->positionY  = intendedCenterY;
    } else if (transform && velocity && !projectile) {
      float previousX       = transform->positionX;
      float previousY       = transform->positionY;
      float intendedCenterX = previousX + velocity->velocityX * deltaTime;
      float intendedCenterY = previousY + velocity->velocityY * deltaTime;
      transform->positionX  = intendedCenterX;
      transform->positionY  = intendedCenterY;
    } else if (transform && velocity) {
      transform->positionX += velocity->velocityX * deltaTime;
      transform->positionY += velocity->velocityY * deltaTime;
    }
  }
}
