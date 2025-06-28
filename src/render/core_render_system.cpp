#include "render/core_render_system.h"
#include "render/entity_renderer.h"
#include "render/projectile_renderer.h"
#include "render/aiming_renderer.h"

CoreRenderSystem &CoreRenderSystem::getInstance()
{
  static CoreRenderSystem instance;
  return instance;
}

CoreRenderSystem::CoreRenderSystem() : sdlRenderer(nullptr) {}

void CoreRenderSystem::setRenderer(SDL_Renderer *renderer)
{
  sdlRenderer = renderer;
}

SDL_Renderer *CoreRenderSystem::getRenderer() const
{
  return sdlRenderer;
}

void CoreRenderSystem::renderAll()
{
  EntityRenderer::getInstance().render();
  ProjectileRenderer::getInstance().render();
  AimingRenderer::getInstance().render();
}
