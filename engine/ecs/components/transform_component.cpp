#include "transform_component.h"

TransformComponent::TransformComponent(float positionX, float positionY, float rotation)
    : positionX(positionX), positionY(positionY), rotation(rotation)
{
}

float TransformComponent::getPositionX() const
{
    return positionX;
}
float TransformComponent::getPositionY() const
{
    return positionY;
}
float TransformComponent::getRotation() const
{
    return rotation;
}
void TransformComponent::setPositionX(float positionX)
{
    this->positionX = positionX;
}
void TransformComponent::setPositionY(float positionY)
{
    this->positionY = positionY;
}
void TransformComponent::setRotation(float rotation)
{
    this->rotation = rotation;
}
