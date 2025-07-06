#include "transform_component.h"

TransformComponent::TransformComponent(float positionX, float positionY) : positionX(positionX), positionY(positionY) {}

float TransformComponent::getPositionX() const
{
    return positionX;
}
float TransformComponent::getPositionY() const
{
    return positionY;
}
void TransformComponent::setPositionX(float positionX)
{
    this->positionX = positionX;
}
void TransformComponent::setPositionY(float positionY)
{
    this->positionY = positionY;
}
