#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
class EntityManager;
class CameraService;
class CoreRenderSystem {
public:
  static CoreRenderSystem& getInstance();
  void                     renderAll(std::uint32_t playerEntityId, EntityManager* entityManager,
                                     CameraService* cameraService);
  void                     setRenderer(SDL_Renderer* rendererPointer);
  SDL_Renderer*            getRenderer() const;

private:
  CoreRenderSystem();
  CoreRenderSystem(const CoreRenderSystem&)            = delete;
  CoreRenderSystem& operator=(const CoreRenderSystem&) = delete;
  SDL_Renderer*     sdlRenderer;
};
