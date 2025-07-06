#pragma once
class IWallRenderer {
public:
  virtual ~IWallRenderer() = default;
  virtual void render()    = 0;
};
class EntityManager;
class CameraService;
class CoreRenderSystem;
class WallRenderer : public IWallRenderer {
public:
  WallRenderer(EntityManager* entityManager, CameraService* cameraService,
               CoreRenderSystem* coreRenderSystem);
  void render() override;

private:
  EntityManager*    entityManager;
  CameraService*    cameraService;
  CoreRenderSystem* coreRenderSystem;
};
