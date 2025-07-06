#pragma once
#include "core/camera_service.h"
#include "core/ecs_builder.h"
#include "core/engine.h"
#include "core/game_facade.h"
#include "core/platform_abstraction.h"
#include "core/render_builder.h"
#include "ecs/systems/aiming_system.h"
#include "ecs/systems/health_system.h"
#include "ecs/systems/input_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/shooting_system.h"
#include "factories/projectile_factory.h"
#include "input/input_handler.h"
#include "render/renderer.h"
#include "render/texture_manager.h"
#include <memory>
#include <string>
class GameBuilder {
public:
  static GameFacade buildGame(const std::string& title, int width, int height) {
    auto inputHandler        = std::make_shared<InputHandler>();
    auto cameraService       = std::make_shared<CameraService>();
    auto renderer            = std::make_shared<Renderer>(cameraService);
    auto textureManager      = std::make_shared<TextureManager>();
    auto platformAbstraction = std::make_shared<PlatformAbstraction>();
    auto entityManager       = ECSBuilder::build();
    auto coreRenderSystem    = RenderBuilder::build(cameraService, entityManager, textureManager);
    std::shared_ptr<IMovementSystem> movementSystem =
        std::make_shared<MovementSystem>(entityManager, inputHandler);
    std::shared_ptr<IInputSystem>  inputSystem  = std::make_shared<InputSystem>(inputHandler);
    std::shared_ptr<IAimingSystem> aimingSystem = std::make_shared<AimingSystem>();
    auto projectileFactory = std::make_shared<ProjectileFactory>(entityManager);
    std::shared_ptr<IShootingSystem> shootingSystem =
        std::make_shared<ShootingSystem>(entityManager, projectileFactory);
    std::shared_ptr<IHealthSystem> healthSystem = std::make_shared<HealthSystem>(entityManager);
    EngineConfig                   config{inputHandler,     renderer,       entityManager,
                        textureManager,   cameraService,  platformAbstraction,
                        coreRenderSystem, movementSystem, inputSystem,
                        aimingSystem,     shootingSystem, healthSystem};
    auto                           engine = std::make_shared<Engine>(std::move(config));
    return GameFacade(engine, title, width, height);
  }
};
