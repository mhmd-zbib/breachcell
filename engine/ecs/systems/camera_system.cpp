#include "camera_system.h"
#include "../components/transform_component.h"
CameraSystem::CameraSystem() : targetEntityId(0) {}
void CameraSystem::setTargetEntity(uint32_t entityId)
{
    targetEntityId = entityId;
}
void CameraSystem::setViewportSize(float width, float height)
{
    viewportWidth = width;
    viewportHeight = height;
}
float CameraSystem::getViewportWidth() const
{
    return viewportWidth;
}
float CameraSystem::getViewportHeight() const
{
    return viewportHeight;
}
void CameraSystem::update(EntityManager& entityManager, float deltaTime)
{
    if (targetEntityId == 0)
        return;
    TransformComponent* transform = entityManager.getComponent<TransformComponent>(targetEntityId);
    if (!transform)
        return;
    float cameraX = transform->getPositionX() - viewportWidth * 0.5f;
    float cameraY = transform->getPositionY() - viewportHeight * 0.5f;
    cameraComponent.setPosition(cameraX, cameraY);
}
CameraComponent* CameraSystem::getCameraComponent()
{
    return &cameraComponent;
}
