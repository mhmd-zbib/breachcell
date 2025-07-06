#pragma once
#include "../components/camera_component.h"
#include "../entity_manager.h"
#include <cstdint>
class CameraSystem
{
  public:
    CameraSystem();
    void setTargetEntity(uint32_t entityId);
    void update(EntityManager& entityManager, float deltaTime);
    CameraComponent* getCameraComponent();
    void setViewportSize(float width, float height);
    float getViewportWidth() const;
    float getViewportHeight() const;

  private:
    uint32_t targetEntityId;
    CameraComponent cameraComponent;
    float viewportWidth;
    float viewportHeight;
};
