#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
class IEntityRenderer;
class IProjectileRenderer;
class IAimingRenderer;
class IWallRenderer;
class EntityManager;
class CameraService;
class ICoreRenderSystem {
public:
  virtual ~ICoreRenderSystem()                                     = default;
  virtual void          setRenderer(SDL_Renderer* rendererPointer) = 0;
  virtual SDL_Renderer* getRenderer() const                        = 0;
  virtual void          renderAll(std::uint32_t playerEntityId, EntityManager* entityManager,
                                  CameraService* cameraService)    = 0;
};
class CoreRenderSystem : public ICoreRenderSystem {
public:
  CoreRenderSystem(IEntityRenderer* entityRenderer, IProjectileRenderer* projectileRenderer,
                   IAimingRenderer* aimingRenderer, IWallRenderer* wallRenderer);
  void          setRenderer(SDL_Renderer* rendererPointer) override;
  SDL_Renderer* getRenderer() const override;
  void          renderAll(std::uint32_t playerEntityId, EntityManager* entityManager,
                          CameraService* cameraService) override;

private:
  SDL_Renderer*        sdlRenderer;
  IEntityRenderer*     entityRenderer;
  IProjectileRenderer* projectileRenderer;
  IAimingRenderer*     aimingRenderer;
  IWallRenderer*       wallRenderer;
};
