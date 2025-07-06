#include "render/core_render_system.h"
#include "core/engine.h"
#include "render/aiming_renderer.h"
#include "render/entity_renderer.h"
#include "render/projectile_renderer.h"
#include "render/wall_renderer.h"

CoreRenderSystem& CoreRenderSystem::getInstance() {
  static CoreRenderSystem instance;
  return instance;
}

CoreRenderSystem::CoreRenderSystem() : sdlRenderer(nullptr) {}

void CoreRenderSystem::setRenderer(SDL_Renderer* renderer) {
  sdlRenderer = renderer;
}

SDL_Renderer* CoreRenderSystem::getRenderer() const {
  return sdlRenderer;
}

void CoreRenderSystem::renderAll(std::uint32_t playerEntityId, EntityManager* entityManager,
                                 CameraService* cameraService) {
  EntityRenderer::getInstance().render();
  ProjectileRenderer::getInstance().render();
  AimingRenderer::getInstance().render(playerEntityId, entityManager, cameraService, this);
  WallRenderer::getInstance().render();
}
