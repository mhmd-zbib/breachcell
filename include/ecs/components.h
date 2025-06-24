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
