#include "factories/projectile_factory.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>

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
  TransformComponent transform;
  transform.positionX = positionX;
  transform.positionY = positionY;
  entityManager.addTransformComponent(entityId, transform);
  VelocityComponent velocity;
  velocity.velocityX = velocityX;
  velocity.velocityY = velocityY;
  entityManager.addVelocityComponent(entityId, velocity);
  CollisionComponent collision = CollisionComponent::createCentered(positionX, positionY, width, height);
  entityManager.addCollisionComponent(entityId, collision);
  ProjectileComponent projectile;
  projectile.lifetime = lifetime;
  projectile.damage = 0.0f;
  projectile.ownerId = ownerId;
  entityManager.addProjectileComponent(entityId, projectile);
  return entityId;
}

std::uint32_t ProjectileFactory::create()
{
  return createProjectile(0.0f, 0.0f, 0.0f, 0.0f, 8.0f, 8.0f, 1.0f, "1", 0);
}
