#include "render/aiming_renderer.h"
#include "core/camera_service.h"
#include "ecs/components.h"
#include "ecs/entity_manager.h"
#include "ecs/systems/aiming_system.h"
#include "render/core_render_system.h"
#include <SDL2/SDL.h>
#include <cmath>
AimingRenderer& AimingRenderer::getInstance() {
  static AimingRenderer instance;
  return instance;
}
void AimingRenderer::render(std::uint32_t playerEntityId, EntityManager* entityManager,
                            CameraService* cameraService, CoreRenderSystem* coreRenderSystem) {
  SDL_Rect            cameraView      = cameraService->getViewRectangle();
  TransformComponent* playerTransform = entityManager->getTransformComponent(playerEntityId);
  AimComponent*       aim             = entityManager->getAimComponent(playerEntityId);
  if (!playerTransform || !aim) {
    return;
  }
  float         angle      = aim->aimAngle;
  float         halfCone   = aim->aimConeHalfAngle;
  SDL_Renderer* renderer   = coreRenderSystem->getRenderer();
  float         lineLength = 400.0f;
  float         startX     = playerTransform->positionX;
  float         startY     = playerTransform->positionY;
  startX -= cameraView.x;
  startY -= cameraView.y;
  float leftAngle  = angle - halfCone;
  float rightAngle = angle + halfCone;
  float leftEndX   = startX + std::cos(leftAngle) * lineLength;
  float leftEndY   = startY + std::sin(leftAngle) * lineLength;
  float rightEndX  = startX + std::cos(rightAngle) * lineLength;
  float rightEndY  = startY + std::sin(rightAngle) * lineLength;
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderDrawLine(renderer, static_cast<int>(startX), static_cast<int>(startY),
                     static_cast<int>(leftEndX), static_cast<int>(leftEndY));
  SDL_RenderDrawLine(renderer, static_cast<int>(startX), static_cast<int>(startY),
                     static_cast<int>(rightEndX), static_cast<int>(rightEndY));
}
