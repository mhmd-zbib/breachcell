#pragma once
class IProjectileRenderer {
public:
  virtual ~IProjectileRenderer() = default;
  virtual void render()          = 0;
};
class EntityManager;
class CameraService;
class CoreRenderSystem;
class ProjectileRenderer : public IProjectileRenderer {
public:
  ProjectileRenderer(EntityManager* entityManager, CameraService* cameraService,
                     CoreRenderSystem* coreRenderSystem);
  void render() override;

private:
  EntityManager*    entityManager;
  CameraService*    cameraService;
  CoreRenderSystem* coreRenderSystem;
};
