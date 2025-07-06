#pragma once
#include "ecs/entity_manager.h"
#include <cstdint>
#include <string>

class ProjectileBuilder {
public:
  explicit ProjectileBuilder(EntityManager* entityManager);
  ProjectileBuilder& setPosition(float x, float y);
  ProjectileBuilder& setVelocity(float vx, float vy);
  ProjectileBuilder& setSize(float width, float height);
  ProjectileBuilder& setLifetime(float lifetime);
  ProjectileBuilder& setTextureId(const std::string& textureId);
  ProjectileBuilder& setOwnerId(std::uint32_t ownerId);
  std::uint32_t      build();

private:
  EntityManager* entityManager;
  float          positionX = 0.0f;
  float          positionY = 0.0f;
  float          velocityX = 0.0f;
  float          velocityY = 0.0f;
  float          width     = 1.0f;
  float          height    = 1.0f;
  float          lifetime  = 1.0f;
  std::string    textureId = "1";
  std::uint32_t  ownerId   = 0;
};
