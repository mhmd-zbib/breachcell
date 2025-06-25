#include "ecs/systems/movement_system.h"
#include "ecs/entity_manager.h"
#include "input/input_handler.h"

MovementSystem &MovementSystem::getInstance()
{
  static MovementSystem instance;
  return instance;
}

MovementSystem::MovementSystem() {}

void MovementSystem::setPlayerEntityId(std::uint32_t id)
{
  playerEntityId = id;
}

void MovementSystem::update(float deltaTime)
{
  EntityManager &entityManager = EntityManager::getInstance();
  InputHandler &inputHandler = InputHandler::getInstance();

  // Define movement speed (pixels per second)
  constexpr float speed = 200.0f;

  // Only update the player entity with input
  auto velocity = entityManager.getVelocityComponent(playerEntityId);
  auto transform = entityManager.getTransformComponent(playerEntityId);
  if (velocity && transform)
  {
    // Reset velocity
    velocity->velocityX = 0.0f;
    velocity->velocityY = 0.0f;

    // WASD movement
    if (inputHandler.isKeyPressed(SDLK_w))
      velocity->velocityY = -speed;
    if (inputHandler.isKeyPressed(SDLK_s))
      velocity->velocityY = speed;
    if (inputHandler.isKeyPressed(SDLK_a))
      velocity->velocityX = -speed;
    if (inputHandler.isKeyPressed(SDLK_d))
      velocity->velocityX = speed;

    // Normalize diagonal movement
    if ((velocity->velocityX != 0.0f) && (velocity->velocityY != 0.0f))
    {
      velocity->velocityX *= 0.7071f;
      velocity->velocityY *= 0.7071f;
    }

    transform->positionX += velocity->velocityX * deltaTime;
    transform->positionY += velocity->velocityY * deltaTime;
  }
}
