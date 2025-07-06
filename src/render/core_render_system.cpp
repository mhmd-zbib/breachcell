#include "render/core_render_system.h"
#include "render/aiming_renderer.h"
#include "render/entity_renderer.h"
#include "render/projectile_renderer.h"
#include "render/wall_renderer.h"

CoreRenderSystem::CoreRenderSystem(EntityRenderer*     entityRendererPointer,
                                   ProjectileRenderer* projectileRendererPointer,
                                   AimingRenderer*     aimingRendererPointer,
                                   WallRenderer*       wallRendererPointer) :
    sdlRenderer(nullptr),
    entityRenderer(entityRendererPointer),
    projectileRenderer(projectileRendererPointer),
    aimingRenderer(aimingRendererPointer),
    wallRenderer(wallRendererPointer) {
}

void CoreRenderSystem::setRenderer(SDL_Renderer* renderer) {
  sdlRenderer = renderer;
}

SDL_Renderer* CoreRenderSystem::getRenderer() const {
  return sdlRenderer;
}

void CoreRenderSystem::renderAll(std::uint32_t playerEntityId, EntityManager* entityManager,
                                 CameraService* cameraService) {
  entityRenderer->render();
  projectileRenderer->render();
  aimingRenderer->render(playerEntityId);
  wallRenderer->render();
}
