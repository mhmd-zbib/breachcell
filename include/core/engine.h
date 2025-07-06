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
#include <memory>

struct EngineConfig {
  std::shared_ptr<InputHandler>        inputHandler;
  std::shared_ptr<Renderer>            renderer;
  std::shared_ptr<EntityManager>       entityManager;
  std::shared_ptr<TextureManager>      textureManager;
  std::shared_ptr<CameraService>       cameraService;
  std::shared_ptr<PlatformAbstraction> platformAbstraction;
  std::shared_ptr<ICoreRenderSystem>   coreRenderSystem;
  std::shared_ptr<IMovementSystem>     movementSystem;
  std::shared_ptr<IInputSystem>        inputSystem;
  std::shared_ptr<IAimingSystem>       aimingSystem;
  std::shared_ptr<IShootingSystem>     shootingSystem;
  std::shared_ptr<IHealthSystem>       healthSystem;
};

class Engine {
public:
  explicit Engine(EngineConfig config);
  bool          initialize(const char* windowTitle, int windowWidth, int windowHeight);
  void          handleInput();
  void          update();
  void          render();
  void          cleanup();
  void          createEntities();
  void          setPlayerEntityId(std::uint32_t id);
  std::uint32_t getPlayerEntityId() const;

private:
  bool                                 running;
  std::shared_ptr<InputHandler>        inputHandler;
  std::shared_ptr<Renderer>            renderer;
  std::shared_ptr<EntityManager>       entityManager;
  std::shared_ptr<TextureManager>      textureManager;
  std::shared_ptr<CameraService>       cameraService;
  std::shared_ptr<PlatformAbstraction> platformAbstraction;
  std::shared_ptr<ICoreRenderSystem>   coreRenderSystem;
  std::shared_ptr<IMovementSystem>     movementSystem;
  std::shared_ptr<IInputSystem>        inputSystem;
  std::shared_ptr<IAimingSystem>       aimingSystem;
  std::shared_ptr<IShootingSystem>     shootingSystem;
  std::shared_ptr<IHealthSystem>       healthSystem;
  SDL_Window*                          window;
  std::uint32_t                        playerEntityId;
};
