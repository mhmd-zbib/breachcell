#pragma once
#include "render/aiming_renderer.h"
#include "render/core_render_system.h"
#include "render/entity_renderer.h"
#include "render/projectile_renderer.h"
#include "render/wall_renderer.h"
#include <memory>
class RenderBuilder {
public:
  static std::shared_ptr<ICoreRenderSystem> build(std::shared_ptr<CameraService>  cameraService,
                                                  std::shared_ptr<EntityManager>  entityManager,
                                                  std::shared_ptr<TextureManager> textureManager) {
    auto coreRenderSystem = std::make_shared<CoreRenderSystem>();
    auto entityRenderer   = std::make_shared<EntityRenderer>(coreRenderSystem, cameraService,
                                                           entityManager, textureManager);
    auto projectileRenderer =
        std::make_shared<ProjectileRenderer>(entityManager, cameraService, coreRenderSystem);
    auto aimingRenderer =
        std::make_shared<AimingRenderer>(entityManager, cameraService, coreRenderSystem);
    auto wallRenderer =
        std::make_shared<WallRenderer>(entityManager, cameraService, coreRenderSystem);
    coreRenderSystem->setRenderers(entityRenderer, projectileRenderer, aimingRenderer,
                                   wallRenderer);
    return coreRenderSystem;
  }
};
