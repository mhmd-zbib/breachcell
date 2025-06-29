#pragma once
#include <cstdint>
#include <stdexcept>
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
  float offsetX;
  float offsetY;
  float boxWidth;
  float boxHeight;
  float getMinX(float ownerX) const { return ownerX + offsetX - boxWidth * 0.5f; }
  float getMaxX(float ownerX) const { return ownerX + offsetX + boxWidth * 0.5f; }
  float getMinY(float ownerY) const { return ownerY + offsetY - boxHeight * 0.5f; }
  float getMaxY(float ownerY) const { return ownerY + offsetY + boxHeight * 0.5f; }
  static CollisionComponent createCentered(float offsetX, float offsetY, float width, float height)
  {
    CollisionComponent c;
    c.offsetX = offsetX;
    c.offsetY = offsetY;
    c.boxWidth = width;
    c.boxHeight = height;
    return c;
  }
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
class CollisionComponentBuilder
{
  float centerX;
  float centerY;
  float leftOffset;
  float rightOffset;
  float topOffset;
  float bottomOffset;

public:
  CollisionComponentBuilder(float centerXValue, float centerYValue)
      : centerX(centerXValue), centerY(centerYValue), leftOffset(0.0f), rightOffset(0.0f), topOffset(0.0f), bottomOffset(0.0f) {}
  CollisionComponentBuilder &setLeftOffset(float offset)
  {
    leftOffset = offset;
    return *this;
  }
  CollisionComponentBuilder &setRightOffset(float offset)
  {
    rightOffset = offset;
    return *this;
  }
  CollisionComponentBuilder &setTopOffset(float offset)
  {
    topOffset = offset;
    return *this;
  }
  CollisionComponentBuilder &setBottomOffset(float offset)
  {
    bottomOffset = offset;
    return *this;
  }
  CollisionComponent build()
  {
    float boxWidth = leftOffset + rightOffset;
    float boxHeight = topOffset + bottomOffset;
    if (boxWidth <= 0.0f || boxHeight <= 0.0f)
      throw std::invalid_argument("CollisionComponentBuilder: boxWidth and boxHeight must be positive");
    CollisionComponent collision;
    collision.offsetX = centerX;
    collision.offsetY = centerY;
    collision.boxWidth = boxWidth;
    collision.boxHeight = boxHeight;
    return collision;
  }
};
class ShooterAimingProvider
{
public:
  virtual ~ShooterAimingProvider() = default;
  virtual float getAimingAngle(std::uint32_t entityId) const = 0;
};
struct AimComponent : public ShooterAimingProvider
{
  float aimAngle;
  float aimConeHalfAngle;
  float currentConeDegrees;
  float targetConeDegrees;
  bool isShooting;
  float standingStillTime;
  float lastVelocityMagnitude;
  float lastUpdateTime;
  float getAimingAngle(std::uint32_t entityId) const override { return aimAngle; }
};
