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
  AimComponent *aim = entityManager.getAimComponent(playerId);
  if (!playerTransform || !aim)
    return;
  float angle = aim->aimAngle;
  float halfCone = aim->aimConeHalfAngle;
  SDL_Renderer *renderer = CoreRenderSystem::getInstance().getRenderer();
  float lineLength = 400.0f;
  float startX = playerTransform->positionX;
  float startY = playerTransform->positionY;
  if (collision)
  {
    startX += collision->offsetX;
    startY += collision->offsetY;
  }
  startX -= cameraView.x;
  startY -= cameraView.y;
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
