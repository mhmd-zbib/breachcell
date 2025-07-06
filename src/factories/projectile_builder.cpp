#include "factories/projectile_builder.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>
#include <iostream>

ProjectileBuilder::ProjectileBuilder() {}

ProjectileBuilder& ProjectileBuilder::setPosition(float x, float y)
{
  positionX = x;
  positionY = y;
  return *this;
}
ProjectileBuilder& ProjectileBuilder::setVelocity(float vx, float vy)
{
  velocityX = vx;
  velocityY = vy;
  return *this;
}
ProjectileBuilder& ProjectileBuilder::setSize(float w, float h)
{
  width = w;
  height = h;
  return *this;
}
ProjectileBuilder& ProjectileBuilder::setLifetime(float l)
{
  lifetime = l;
  return *this;
}
ProjectileBuilder& ProjectileBuilder::setTextureId(const std::string& id)
{
  textureId = id;
  return *this;
}
ProjectileBuilder& ProjectileBuilder::setOwnerId(std::uint32_t id)
{
  ownerId = id;
  return *this;
}
std::uint32_t ProjectileBuilder::build()
{
  if (width <= 0.0f || height <= 0.0f)
  {
    throw std::invalid_argument("ProjectileBuilder: width and height must be positive");
  }

  if (lifetime <= 0.0f)
  {
    throw std::invalid_argument("ProjectileBuilder: lifetime must be positive");
  }

  if (textureId.empty())
  {
    throw std::invalid_argument("ProjectileBuilder: textureId must not be empty");
  }

  EntityManager& entityManager = EntityManager::getInstance();
  std::uint32_t entityId = entityManager.createEntity();
  TransformComponent transform{positionX, positionY, 0.0f, 1.0f};
  VelocityComponent velocity{velocityX, velocityY};
  ProjectileComponent projectile;
  projectile.lifetime = lifetime;
  projectile.damage = 0.0f;
  projectile.ownerId = ownerId;
  projectile.framesAlive = 0;
  entityManager.addTransformComponent(entityId, transform);
  entityManager.addVelocityComponent(entityId, velocity);
  entityManager.addProjectileComponent(entityId, projectile);
  std::cout << "ProjectileBuilder: Created projectile entity " << entityId << " at (" << positionX <<
            ", " << positionY << ") with velocity (" << velocityX << ", " << velocityY << ") and ownerId " <<
            ownerId << std::endl;
  return entityId;
}
