#include "core/camera_service.h"
#include "core/engine.h"
#include "core/platform_abstraction.h"
#include "ecs/entity_manager.h"
#include "ecs/systems/aiming_system.h"
#include "ecs/systems/health_system.h"
#include "ecs/systems/input_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/shooting_system.h"
#include "input/input_handler.h"
#include "render/core_render_system.h"
#include "render/renderer.h"
#include "render/texture_manager.h"

int main() {
  InputHandler*        inputHandler        = &InputHandler::getInstance();
  Renderer*            renderer            = &Renderer::getInstance();
  EntityManager*       entityManager       = &EntityManager::getInstance();
  TextureManager*      textureManager      = &TextureManager::getInstance();
  CameraService*       cameraService       = &CameraService::getInstance();
  PlatformAbstraction* platformAbstraction = &PlatformAbstraction::getInstance();
  CoreRenderSystem*    coreRenderSystem    = &CoreRenderSystem::getInstance();
  MovementSystem*      movementSystem      = &MovementSystem::getInstance();
  InputSystem*         inputSystem         = &InputSystem::getInstance();
  AimingSystem*        aimingSystem        = &AimingSystem::getInstance();
  ShootingSystem*      shootingSystem      = &ShootingSystem::getInstance();
  HealthSystem*        healthSystem        = &HealthSystem::getInstance();
  Engine               engine(inputHandler, renderer, entityManager, textureManager, cameraService,
                              platformAbstraction, coreRenderSystem, movementSystem, inputSystem, aimingSystem,
                              shootingSystem, healthSystem);
  if (!engine.initialize("BreachCell", 800, 600)) {
    return 1;
  }
  engine.run();
  engine.clean();
  return 0;
}
