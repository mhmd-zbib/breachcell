#include "ecs/systems/render_system.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include "render/renderer.h"
#include "ecs/systems/aiming_system.h"
#include "core/engine.h"
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>

static SDL_Texture *loadTexture(const char *filePath, SDL_Renderer *renderer)
{
  SDL_Surface *surface = IMG_Load(filePath);
  if (!surface)
    return nullptr;
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

RenderSystem &RenderSystem::getInstance()
{
  static RenderSystem instance;
  return instance;
}

RenderSystem::RenderSystem() : playerTextureId(0) {}

RenderSystem::~RenderSystem() { unloadTextures(); }

void RenderSystem::loadTextures()
{
  Renderer &renderer = Renderer::getInstance();
  SDL_Renderer *sdlRenderer = renderer.getSDLRenderer();
  playerTextureId = 1;
  SDL_Texture *playerTexture = loadTexture("assets/player.png", sdlRenderer);
  if (!playerTexture)
  {
    std::cerr << "Failed to load player texture: assets/player.png\n";
    std::cerr << "SDL_image error: " << IMG_GetError() << std::endl;
    std::exit(1);
  }
  textures[playerTextureId] = playerTexture;
}

void RenderSystem::unloadTextures()
{
  for (auto &pair : textures)
    if (pair.second)
      SDL_DestroyTexture(pair.second);
  textures.clear();
}

void RenderSystem::renderAll()
{
  Renderer &renderer = Renderer::getInstance();
  SDL_Renderer *sdlRenderer = renderer.getSDLRenderer();
  if (!sdlRenderer)
  {
    std::cerr << "RenderSystem error: SDL_Renderer is null" << std::endl;
    std::exit(1);
  }
  EntityManager &entityManager = EntityManager::getInstance();
  bool anyRendered = false;
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    TransformComponent *transform = nullptr;
    SpriteComponent *sprite = nullptr;
    try
    {
      transform = entityManager.getTransformComponent(entityId);
      sprite = entityManager.getSpriteComponent(entityId);
    }
    catch (const std::exception &e)
    {
      std::cerr << "RenderSystem error: Exception accessing components for entity " << entityId << ": " << e.what() << std::endl;
      continue;
    }
    if (!transform && !sprite)
      continue;
    if (!transform && sprite)
    {
      std::cerr << "RenderSystem warning: SpriteComponent found but TransformComponent missing for entity " << entityId << std::endl;
      continue;
    }
    if (transform && !sprite)
    {
      ProjectileComponent *projectile = entityManager.getProjectileComponent(entityId);
      if (projectile)
        continue;
      std::cerr << "RenderSystem warning: TransformComponent found but SpriteComponent missing for entity " << entityId << std::endl;
      continue;
    }
    if (transform && sprite)
    {
      if (sprite->textureId != playerTextureId)
      {
        std::cerr << "RenderSystem warning: Unknown textureId " << sprite->textureId << " for entity " << entityId << std::endl;
        continue;
      }
      SDL_Rect dstRect;
      dstRect.x = static_cast<int>(transform->positionX);
      dstRect.y = static_cast<int>(transform->positionY);
      dstRect.w = PLAYER_TEXTURE_WIDTH;
      dstRect.h = PLAYER_TEXTURE_HEIGHT;
      SDL_Texture *texture = nullptr;
      try
      {
        texture = textures.at(sprite->textureId);
      }
      catch (const std::exception &e)
      {
        std::cerr << "RenderSystem error: Texture not found for entity " << entityId << ", textureId " << sprite->textureId << ": " << e.what() << std::endl;
        continue;
      }
      if (!texture)
      {
        std::cerr << "RenderSystem error: Texture pointer is null for entity " << entityId << ", textureId " << sprite->textureId << std::endl;
        continue;
      }
      if (SDL_RenderCopy(sdlRenderer, texture, nullptr, &dstRect) != 0)
      {
        std::cerr << "RenderSystem error: SDL_RenderCopy failed for entity " << entityId << ", SDL error: " << SDL_GetError() << std::endl;
      }
      anyRendered = true;
    }
  }
  if (!anyRendered)
    std::cerr << "RenderSystem warning: No entities rendered this frame" << std::endl;
}

void RenderSystem::renderAimLine()
{
  std::uint32_t playerId = Engine::getInstance(InputHandler::getInstance(), Renderer::getInstance()).getPlayerEntityId();
  EntityManager &entityManager = EntityManager::getInstance();
  TransformComponent *playerTransform = entityManager.getTransformComponent(playerId);
  if (!playerTransform)
    return;
  float angle = AimingSystem::getInstance().getAimAngle();
  Renderer &renderer = Renderer::getInstance();
  SDL_Renderer *sdlRenderer = renderer.getSDLRenderer();
  float lineLength = 100.0f;
  float startX = playerTransform->positionX + PLAYER_TEXTURE_WIDTH / 2;
  float startY = playerTransform->positionY + PLAYER_TEXTURE_HEIGHT / 2;
  float halfCone = 17.5f * 3.14159265f / 180.0f;
  float leftAngle = angle - halfCone;
  float rightAngle = angle + halfCone;
  float leftEndX = startX + std::cos(leftAngle) * lineLength;
  float leftEndY = startY + std::sin(leftAngle) * lineLength;
  float rightEndX = startX + std::cos(rightAngle) * lineLength;
  float rightEndY = startY + std::sin(rightAngle) * lineLength;
  SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
  SDL_RenderDrawLine(sdlRenderer, static_cast<int>(startX), static_cast<int>(startY), static_cast<int>(leftEndX), static_cast<int>(leftEndY));
  SDL_RenderDrawLine(sdlRenderer, static_cast<int>(startX), static_cast<int>(startY), static_cast<int>(rightEndX), static_cast<int>(rightEndY));
}

void RenderSystem::renderProjectiles()
{
  Renderer &renderer = Renderer::getInstance();
  SDL_Renderer *sdlRenderer = renderer.getSDLRenderer();
  EntityManager &entityManager = EntityManager::getInstance();
  for (std::uint32_t entityId = 1; entityId < EntityManager::MAX_ENTITY_ID; ++entityId)
  {
    ProjectileComponent *projectile = entityManager.getProjectileComponent(entityId);
    TransformComponent *transform = entityManager.getTransformComponent(entityId);
    if (!projectile || !transform)
      continue;
    int centerX = static_cast<int>(transform->positionX);
    int centerY = static_cast<int>(transform->positionY);
    int radius = 4;
    SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
    for (int w = 0; w < radius * 2; w++)
    {
      for (int h = 0; h < radius * 2; h++)
      {
        int dx = radius - w;
        int dy = radius - h;
        if (dx * dx + dy * dy <= radius * radius)
        {
          SDL_RenderDrawPoint(sdlRenderer, centerX + dx, centerY + dy);
        }
      }
    }
  }
}