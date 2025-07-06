#include "factories/projectile_factory.h"
#include "ecs/components.h"
#include "ecs/entity_manager.h"
#include "factories/projectile_builder.h"
#include <iostream>
#include <stdexcept>

ProjectileFactory& ProjectileFactory::getInstance()
{
  static ProjectileFactory instance;
  return instance;
}

ProjectileFactory::ProjectileFactory() {}

void ProjectileFactory::validateParameters(float positionX, float positionY, float velocityX,
                                           float velocityY, float width, float height,
                                           float lifetime, const std::string& textureId)
{
  if (width <= 0.0f || height <= 0.0f)
  {
    throw std::invalid_argument("ProjectileFactory: width and height must be positive");
  }

  if (lifetime <= 0.0f)
  {
    throw std::invalid_argument("ProjectileFactory: lifetime must be positive");
  }

  if (textureId.empty())
  {
    throw std::invalid_argument("ProjectileFactory: textureId must not be empty");
  }
}

std::uint32_t ProjectileFactory::createProjectile(float positionX, float positionY, float velocityX,
                                                  float velocityY, float width, float height,
                                                  float lifetime, const std::string& textureId,
                                                  std::uint32_t ownerId)
{
  return ProjectileBuilder()
      .setPosition(positionX, positionY)
      .setVelocity(velocityX, velocityY)
      .setSize(width, height)
      .setLifetime(lifetime)
      .setTextureId(textureId)
      .setOwnerId(ownerId)
      .build();
}

std::uint32_t ProjectileFactory::create()
{
  return createProjectile(0.0f, 0.0f, 0.0f, 0.0f, 8.0f, 8.0f, 1.0f, "1", 0);
}
