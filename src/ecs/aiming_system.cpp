#include "ecs/systems/aiming_system.h"
#include "ecs/entity_manager.h"
#include "core/math_utils.h"
#include "core/camera_service.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <algorithm>
#include "input/input_handler.h"

AimingSystem::AimingSystem() {}

void AimingSystem::triggerPostShotConeExpansion(std::uint32_t playerEntityId)
{
  EntityManager& entityManager = EntityManager::getInstance();
  VelocityComponent* playerVelocity = entityManager.getVelocityComponent(playerEntityId);
  float velocityMagnitude = playerVelocity ? MathUtils::vectorMagnitude(playerVelocity->velocityX,
                            playerVelocity->velocityY) : 0.0f;
  bool isStanding = velocityMagnitude < 1e-3f;

  if (isStanding && standingStillTime >= 2.0f)
  {
    targetConeDegrees = STANDING_CONE_DEGREES;
    currentConeDegrees = targetConeDegrees;
    standingStillTime = 0.0f;
  }
}

void AimingSystem::update(std::uint32_t playerEntityId, float mouseX, float mouseY)
{
  EntityManager& entityManager = EntityManager::getInstance();
  TransformComponent* playerTransform = entityManager.getTransformComponent(playerEntityId);
  VelocityComponent* playerVelocity = entityManager.getVelocityComponent(playerEntityId);
  AimComponent* playerAim = entityManager.getAimComponent(playerEntityId);

  if (!playerTransform || !playerAim)
  {
    return;
  }

  float playerCenterX = playerTransform->positionX;
  float playerCenterY = playerTransform->positionY;
  int windowX = 0;
  int windowY = 0;
  SDL_GetWindowPosition(SDL_GetWindowFromID(1), &windowX, &windowY);
  SDL_Rect cameraView = CameraService::getInstance().getViewRectangle();
  float worldMouseX = mouseX + cameraView.x;
  float worldMouseY = mouseY + cameraView.y;
  float deltaX = worldMouseX - playerCenterX;
  float deltaY = worldMouseY - playerCenterY;
  float newAimAngle = std::atan2(deltaY, deltaX);

  if (std::abs(newAimAngle - playerAim->aimAngle) > MathUtils::PI)
  {
    if (newAimAngle > playerAim->aimAngle)
    {
      playerAim->aimAngle += 2 * MathUtils::PI;
    }
    else
    {
      playerAim->aimAngle -= 2 * MathUtils::PI;
    }
  }

  float aimLerpSpeed = 20.0f;
  float prevAimAngle = playerAim->aimAngle;
  playerAim->aimAngle += (newAimAngle - playerAim->aimAngle) * std::clamp(aimLerpSpeed * 0.016f, 0.0f,
                         1.0f);
  float velocityMagnitude = playerVelocity ? MathUtils::vectorMagnitude(playerVelocity->velocityX,
                            playerVelocity->velocityY) : 0.0f;
  InputHandler& inputHandler = InputHandler::getInstance();
  static Uint32 lastUpdateTicks = 0;
  Uint32 now = SDL_GetTicks();
  float deltaTime = 0.016f;

  if (lastUpdateTicks > 0)
  {
    deltaTime = std::min((now - lastUpdateTicks) / 1000.0f, 0.033f);
  }

  lastUpdateTicks = now;
  bool isStanding = velocityMagnitude < 1e-3f;
  bool shooting = playerAim->isShooting;

  if (isStanding)
  {
    if (shooting)
    {
      if (playerAim->standingStillTime >= 2.0f)
      {
        playerAim->targetConeDegrees = 6.0f;
        playerAim->standingStillTime = 0.0f;
      }
      else
      {
        playerAim->targetConeDegrees = 6.0f;
        playerAim->standingStillTime = 0.0f;
      }
    }
    else
    {
      playerAim->standingStillTime += deltaTime;

      if (playerAim->standingStillTime >= 2.0f)
      {
        playerAim->targetConeDegrees = 2.0f;
      }
      else
      {
        playerAim->targetConeDegrees = 6.0f;
      }
    }
  }
  else
  {
    playerAim->standingStillTime = 0.0f;

    if (inputHandler.isKeyPressed(SDLK_LSHIFT) || inputHandler.isKeyPressed(SDLK_RSHIFT))
    {
      playerAim->targetConeDegrees = 10.0f;
    }
    else
    {
      playerAim->targetConeDegrees = 18.0f;
    }
  }

  float transitionSpeed = 40.0f * deltaTime;
  float delta = playerAim->targetConeDegrees - playerAim->currentConeDegrees;

  if (std::abs(delta) < transitionSpeed)
  {
    playerAim->currentConeDegrees = playerAim->targetConeDegrees;
  }
  else
  {
    playerAim->currentConeDegrees += (delta > 0 ? 1 : -1) * transitionSpeed;
  }

  playerAim->aimConeHalfAngle = 0.5f * MathUtils::toRadians(playerAim->currentConeDegrees);
  playerAim->lastVelocityMagnitude = velocityMagnitude;
}
void AimingSystem::update(std::uint32_t playerEntityId)
{
  int mouseX = 0;
  int mouseY = 0;
  SDL_GetMouseState(&mouseX, &mouseY);
  update(playerEntityId, static_cast<float>(mouseX), static_cast<float>(mouseY));
}
float AimingSystem::getAimAngle() const
{
  return aimAngle;
}
float AimingSystem::getAimConeHalfAngle() const
{
  return aimConeHalfAngle;
}
float AimingSystem::getShootConeHalfAngle(std::uint32_t playerEntityId) const
{
  EntityManager& entityManager = EntityManager::getInstance();
  AimComponent* aim = entityManager.getAimComponent(playerEntityId);

  if (!aim)
  {
    throw std::runtime_error("AimComponent not found for entity");
  }

  return aim->aimConeHalfAngle;
}
AimingSystem& AimingSystem::getInstance()
{
  static AimingSystem instance;
  return instance;
}
