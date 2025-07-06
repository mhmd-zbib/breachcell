#pragma once
#include <SDL2/SDL.h>

class IEntityRenderer {
public:
  virtual ~IEntityRenderer() = default;
  virtual void render()      = 0;
};

class CoreRenderSystem;
class CameraService;
class EntityManager;
class TextureManager;

class EntityRenderer : public IEntityRenderer {
public:
  EntityRenderer(CoreRenderSystem* coreRenderSystem, CameraService* cameraService,
                 EntityManager* entityManager, TextureManager* textureManager);
  void render() override;
  void renderCross(SDL_Renderer* rendererPointer, float centerX, float centerY, float crossSize,
                   SDL_Color crossColor);

private:
  CoreRenderSystem* coreRenderSystem;
  CameraService*    cameraService;
  EntityManager*    entityManager;
  TextureManager*   textureManager;
};
