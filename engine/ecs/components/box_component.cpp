#include "box_component.h"

BoxComponent::BoxComponent(float width, float height, unsigned char red, unsigned char green, unsigned char blue,
                           unsigned char alpha)
    : width(width), height(height), red(red), green(green), blue(blue), alpha(alpha)
{
}

float BoxComponent::getWidth() const
{
    return width;
}
float BoxComponent::getHeight() const
{
    return height;
}
unsigned char BoxComponent::getRed() const
{
    return red;
}
unsigned char BoxComponent::getGreen() const
{
    return green;
}
unsigned char BoxComponent::getBlue() const
{
    return blue;
}
unsigned char BoxComponent::getAlpha() const
{
    return alpha;
}
