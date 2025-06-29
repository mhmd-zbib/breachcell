#include "render/aiming_renderer.h"
#include "core/engine.h"
#include "ecs/systems/aiming_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/core_render_system.h"
#include "core/camera_service.h"
#include <SDL2/SDL.h>
#include <cmath>
AimingRenderer &AimingRenderer::getInstance()
{
  static AimingRenderer instance;
  return instance;
}
void AimingRenderer::render()
{
  std::uint32_t playerId = Engine::getInstance().getPlayerEntityId();
  EntityManager &entityManager = EntityManager::getInstance();
  SDL_Rect cameraView = CameraService::getInstance().getViewRectangle();
  TransformComponent *playerTransform = entityManager.getTransformComponent(playerId);
  CollisionComponent *collision = entityManager.getCollisionComponent(playerId);
  if (!playerTransform)
    return;
  std::printf("Player position: %.2f, %.2f\n", playerTransform->positionX, playerTransform->positionY);
  float angle = AimingSystem::getInstance().getAimAngle();
  float halfCone = AimingSystem::getInstance().getAimConeHalfAngle();
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  float lineLength = 400.0f;
  float startX = playerTransform->positionX - cameraView.x;
  float startY = playerTransform->positionY - cameraView.y;
  if (collision)
  {
    startX = playerTransform->positionX + collision->offsetX - cameraView.x;
    startY = playerTransform->positionY + collision->offsetY - cameraView.y;
  }
  float leftAngle = angle - halfCone;
  float rightAngle = angle + halfCone;
  float leftEndX = startX + std::cos(leftAngle) * lineLength;
  float leftEndY = startY + std::sin(leftAngle) * lineLength;
  float rightEndX = startX + std::cos(rightAngle) * lineLength;
  float rightEndY = startY + std::sin(rightAngle) * lineLength;
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawLine(renderer, static_cast<int>(startX), static_cast<int>(startY), static_cast<int>(leftEndX), static_cast<int>(leftEndY));
  SDL_RenderDrawLine(renderer, static_cast<int>(startX), static_cast<int>(startY), static_cast<int>(rightEndX), static_cast<int>(rightEndY));
}
