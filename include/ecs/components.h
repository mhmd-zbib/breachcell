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
  float centerX;
  float centerY;
  float boxWidth;
  float boxHeight;
  float getMinX() const { return centerX - boxWidth * 0.5f; }
  float getMaxX() const { return centerX + boxWidth * 0.5f; }
  float getMinY() const { return centerY - boxHeight * 0.5f; }
  float getMaxY() const { return centerY + boxHeight * 0.5f; }
  void setCenter(float x, float y)
  {
    centerX = x;
    centerY = y;
  }
  void setSize(float width, float height)
  {
    boxWidth = width;
    boxHeight = height;
  }
  static CollisionComponent createCentered(float centerX, float centerY, float width, float height)
  {
    CollisionComponent c;
    c.centerX = centerX;
    c.centerY = centerY;
    c.boxWidth = width;
    c.boxHeight = height;
    return c;
  }
  bool containsPoint(float pointX, float pointY) const
  {
    return pointX >= getMinX() && pointX <= getMaxX() && pointY >= getMinY() && pointY <= getMaxY();
  }
  bool intersects(const CollisionComponent &other) const
  {
    return getMinX() < other.getMaxX() && getMaxX() > other.getMinX() && getMinY() < other.getMaxY() && getMaxY() > other.getMinY();
  }
  void moveToCenter(float newCenterX, float newCenterY)
  {
    centerX = newCenterX;
    centerY = newCenterY;
  }
  void resizeFromCenter(float newWidth, float newHeight)
  {
    boxWidth = newWidth;
    boxHeight = newHeight;
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
    collision.centerX = centerX;
    collision.centerY = centerY;
    collision.boxWidth = boxWidth;
    collision.boxHeight = boxHeight;
    return collision;
  }
};
