#pragma once
#include <cstdint>
class EntityManager;
class ICameraTrackingStrategy
{
  public:
    virtual ~ICameraTrackingStrategy() = default;
    virtual void updateCameraPosition(float& cameraPosX, float& cameraPosY, EntityManager* entityManager,
                                      uint32_t targetEntityId) = 0;
};
