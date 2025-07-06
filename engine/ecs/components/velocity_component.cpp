#include "velocity_component.h"

VelocityComponent::VelocityComponent(float velocityX, float velocityY) : velocityX(velocityX), velocityY(velocityY) {}

float VelocityComponent::getVelocityX() const
{
    return velocityX;
}
float VelocityComponent::getVelocityY() const
{
    return velocityY;
}
void VelocityComponent::setVelocityX(float velocityX)
{
    this->velocityX = velocityX;
}
void VelocityComponent::setVelocityY(float velocityY)
{
    this->velocityY = velocityY;
}
