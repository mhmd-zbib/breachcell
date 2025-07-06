#pragma once
#include <cstdint>

class EntityManager;
class CameraService;
class CoreRenderSystem;

class AimingRenderer {
public:
  static AimingRenderer& getInstance();
  void                   render(std::uint32_t playerEntityId, EntityManager* entityManager,
                                CameraService* cameraService, CoreRenderSystem* coreRenderSystem);

private:
  AimingRenderer()                                 = default;
  AimingRenderer(const AimingRenderer&)            = delete;
  AimingRenderer& operator=(const AimingRenderer&) = delete;
};
