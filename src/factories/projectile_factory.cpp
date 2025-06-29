#include "factories/projectile_factory.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>
#include <iostream>

ProjectileFactory &ProjectileFactory::getInstance()
{
  static ProjectileFactory instance;
  return instance;
}

ProjectileFactory::ProjectileFactory() {}

void ProjectileFactory::validateParameters(float positionX, float positionY, float velocityX, float velocityY, float width, float height, float lifetime, const std::string &textureId)
{
  if (width <= 0.0f || height <= 0.0f)
    throw std::invalid_argument("ProjectileFactory: width and height must be positive");
  if (lifetime <= 0.0f)
    throw std::invalid_argument("ProjectileFactory: lifetime must be positive");
  if (textureId.empty())
    throw std::invalid_argument("ProjectileFactory: textureId must not be empty");
}

std::uint32_t ProjectileFactory::createProjectile(float positionX, float positionY, float velocityX, float velocityY, float width, float height, float lifetime, const std::string &textureId, std::uint32_t ownerId)
{
  validateParameters(positionX, positionY, velocityX, velocityY, width, height, lifetime, textureId);
  EntityManager &entityManager = EntityManager::getInstance();
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
  std::cout << "ProjectileFactory: Created projectile entity " << entityId << " at (" << positionX << ", " << positionY << ") with velocity (" << velocityX << ", " << velocityY << ") and ownerId " << ownerId << std::endl;
  return entityId;
}

std::uint32_t ProjectileFactory::create()
{
  return createProjectile(0.0f, 0.0f, 0.0f, 0.0f, 8.0f, 8.0f, 1.0f, "1", 0);
}
