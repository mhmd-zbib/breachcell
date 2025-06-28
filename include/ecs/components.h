#pragma once
#include <cstdint>
struct TransformComponent
{
  float positionX;
  float positionY;
  float rotation;
  float scale;
};
struct VelocityComponent
{
  float velocityX;
  float velocityY;
};
struct SpriteComponent
{
  std::uint32_t textureId;
  int drawOrder;
};
struct InputComponent
{
  bool upPressed;
  bool downPressed;
  bool leftPressed;
  bool rightPressed;
};
struct ProjectileComponent
{
  float lifetime;
  float damage;
  std::uint32_t ownerId;
};
struct CollisionComponent
{
  float boxX;
  float boxY;
  float boxWidth;
  float boxHeight;
};
struct HealthComponent
{
  float value;
  float minValue;
  float maxValue;
  void increment(float amount)
  {
    value += amount;
    if (value > maxValue)
      value = maxValue;
  }
  void decrement(float amount)
  {
    value -= amount;
    if (value < minValue)
      value = minValue;
  }
  float getValue() const
  {
    return value;
  }
  float getMaxValue() const
  {
    return maxValue;
  }
  float getMinValue() const
  {
    return minValue;
  }
};
