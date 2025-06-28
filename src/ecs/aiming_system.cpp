#include "ecs/systems/aiming_system.h"
#include "ecs/entity_manager.h"
#include "core/math_utils.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <algorithm>
#include "input/input_handler.h"
AimingSystem &AimingSystem::getInstance()
{
  static AimingSystem instance;
  return instance;
}
AimingSystem::AimingSystem() {}
void AimingSystem::setPlayerEntityId(std::uint32_t id)
{
  playerEntityId = id;
}
void AimingSystem::setShooting(bool shooting)
{
  isShooting = shooting;
}

void AimingSystem::triggerPostShotConeExpansion()
{
  EntityManager &entityManager = EntityManager::getInstance();
  VelocityComponent *playerVelocity = entityManager.getVelocityComponent(playerEntityId);
  float velocityMagnitude = playerVelocity ? MathUtils::vectorMagnitude(playerVelocity->velocityX, playerVelocity->velocityY) : 0.0f;
  bool isStanding = velocityMagnitude < 1e-3f;
  if (isStanding && standingStillTime >= 2.0f)
  {
    targetConeDegrees = STANDING_CONE_DEGREES;
    currentConeDegrees = targetConeDegrees;
    standingStillTime = 0.0f;
  }
}

void AimingSystem::update(float mouseX, float mouseY)
{
  EntityManager &entityManager = EntityManager::getInstance();
  TransformComponent *playerTransform = entityManager.getTransformComponent(playerEntityId);
  VelocityComponent *playerVelocity = entityManager.getVelocityComponent(playerEntityId);
  if (!playerTransform)
    return;
  float playerCenterX = playerTransform->positionX + 32.0f;
  float playerCenterY = playerTransform->positionY + 32.0f;
  float dx = mouseX - playerCenterX;
  float dy = mouseY - playerCenterY;
  float newAimAngle = std::atan2(dy, dx);
  if (std::abs(newAimAngle - aimAngle) > MathUtils::PI)
  {
    if (newAimAngle > aimAngle)
      aimAngle += 2 * MathUtils::PI;
    else
      aimAngle -= 2 * MathUtils::PI;
  }
  float aimLerpSpeed = 20.0f;
  aimAngle += (newAimAngle - aimAngle) * std::clamp(aimLerpSpeed * 0.016f, 0.0f, 1.0f);
  float velocityMagnitude = playerVelocity ? MathUtils::vectorMagnitude(playerVelocity->velocityX, playerVelocity->velocityY) : 0.0f;
  InputHandler &inputHandler = InputHandler::getInstance();
  static Uint32 lastUpdateTicks = 0;
  Uint32 now = SDL_GetTicks();
  float deltaTime = 0.016f;
  if (lastUpdateTicks > 0)
    deltaTime = std::min((now - lastUpdateTicks) / 1000.0f, 0.033f);
  lastUpdateTicks = now;
  bool isStanding = velocityMagnitude < 1e-3f;
  static bool wasShooting = false;
  bool shooting = isShooting;
  if (isStanding)
  {
    if (shooting)
    {
      if (standingStillTime >= 2.0f)
      {
        targetConeDegrees = STANDING_CONE_DEGREES;
        standingStillTime = 0.0f;
      }
      else
      {
        targetConeDegrees = STANDING_CONE_DEGREES;
        standingStillTime = 0.0f;
      }
    }
    else
    {
      standingStillTime += deltaTime;
      if (standingStillTime >= 2.0f)
      {
        targetConeDegrees = STANDING_FOCUSED_CONE_DEGREES;
      }
      else
      {
        targetConeDegrees = STANDING_CONE_DEGREES;
      }
    }
  }
  else
  {
    standingStillTime = 0.0f;
    if (inputHandler.isKeyPressed(SDLK_LSHIFT) || inputHandler.isKeyPressed(SDLK_RSHIFT))
    {
      targetConeDegrees = SLOW_WALK_CONE_DEGREES;
    }
    else
    {
      targetConeDegrees = WALKING_CONE_DEGREES;
    }
  }
  wasShooting = shooting;
  float transitionSpeed = coneTransitionSpeed * deltaTime;
  float delta = targetConeDegrees - currentConeDegrees;
  if (std::abs(delta) < transitionSpeed)
    currentConeDegrees = targetConeDegrees;
  else
    currentConeDegrees += (delta > 0 ? 1 : -1) * transitionSpeed;
  aimConeHalfAngle = 0.5f * MathUtils::toRadians(currentConeDegrees);
  lastVelocityMagnitude = velocityMagnitude;
}
void AimingSystem::update()
{
  int mouseX = 0;
  int mouseY = 0;
  SDL_GetMouseState(&mouseX, &mouseY);
  update(static_cast<float>(mouseX), static_cast<float>(mouseY));
}
float AimingSystem::getAimAngle() const
{
  return aimAngle;
}
float AimingSystem::getAimConeHalfAngle() const
{
  return aimConeHalfAngle;
}
float AimingSystem::getShootConeHalfAngle() const
{
  EntityManager &entityManager = EntityManager::getInstance();
  VelocityComponent *playerVelocity = entityManager.getVelocityComponent(playerEntityId);
  float velocityMag = 0.0f;
  if (playerVelocity)
    velocityMag = MathUtils::vectorMagnitude(playerVelocity->velocityX, playerVelocity->velocityY);
  float coneDegrees = STANDING_SHOOT_CONE_DEGREES;
  if (velocityMag >= 1e-3f)
  {
    InputHandler &inputHandler = InputHandler::getInstance();
    if (inputHandler.isKeyPressed(SDLK_LSHIFT) || inputHandler.isKeyPressed(SDLK_RSHIFT))
      coneDegrees = SLOW_WALK_SHOOT_CONE_DEGREES;
    else
      coneDegrees = WALKING_SHOOT_CONE_DEGREES;
  }
  return 0.5f * MathUtils::toRadians(coneDegrees);
}
