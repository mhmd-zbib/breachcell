#include "camera_component.h"
CameraComponent::CameraComponent() : positionX(0), positionY(0), zoom(1.0f), rotation(0) {}
void CameraComponent::setPosition(float positionX, float positionY)
{
    this->positionX = positionX;
    this->positionY = positionY;
}
void CameraComponent::setZoom(float zoomLevel)
{
    zoom = zoomLevel;
}
void CameraComponent::setRotation(float angle)
{
    rotation = angle;
}
float CameraComponent::getPositionX() const
{
    return positionX;
}
float CameraComponent::getPositionY() const
{
    return positionY;
}
float CameraComponent::getZoom() const
{
    return zoom;
}
float CameraComponent::getRotation() const
{
    return rotation;
}
