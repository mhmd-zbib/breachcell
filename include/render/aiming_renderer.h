#pragma once
#include <cstdint>

class IAimingRenderer {
public:
  virtual ~IAimingRenderer()                        = default;
  virtual void render(std::uint32_t playerEntityId) = 0;
};

class EntityManager;
class CameraService;
class CoreRenderSystem;

class AimingRenderer : public IAimingRenderer {
public:
  AimingRenderer(EntityManager* entityManager, CameraService* cameraService,
                 CoreRenderSystem* coreRenderSystem);
  void render(std::uint32_t playerEntityId) override;

private:
  EntityManager*    entityManager;
  CameraService*    cameraService;
  CoreRenderSystem* coreRenderSystem;
};
