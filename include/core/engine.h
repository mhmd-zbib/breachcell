#pragma once
#include "core/camera_service.h"
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
#include <cstdint>

class Engine {
public:
  Engine(InputHandler* inputHandler, Renderer* renderer, EntityManager* entityManager,
         TextureManager* textureManager, CameraService* cameraService,
         PlatformAbstraction* platformAbstraction, CoreRenderSystem* coreRenderSystem,
         MovementSystem* movementSystem, InputSystem* inputSystem, AimingSystem* aimingSystem,
         ShootingSystem* shootingSystem, HealthSystem* healthSystem);
  bool          initialize(const char* windowTitle, int windowWidth, int windowHeight);
  void          run();
  void          handleInput();
  void          update();
  void          render();
  void          clean();
  void          createEntities();
  void          setPlayerEntityId(std::uint32_t id);
  std::uint32_t getPlayerEntityId() const;

private:
  bool                 running;
  InputHandler*        inputHandler;
  Renderer*            renderer;
  EntityManager*       entityManager;
  TextureManager*      textureManager;
  CameraService*       cameraService;
  PlatformAbstraction* platformAbstraction;
  CoreRenderSystem*    coreRenderSystem;
  MovementSystem*      movementSystem;
  InputSystem*         inputSystem;
  AimingSystem*        aimingSystem;
  ShootingSystem*      shootingSystem;
  HealthSystem*        healthSystem;
  SDL_Window*          window;
  std::uint32_t        playerEntityId;
};
