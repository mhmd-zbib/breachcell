#include "factories/wall_factory.h"
#include "ecs/entity_manager.h"
#include "ecs/components.h"
#include <stdexcept>

WallFactory& WallFactory::getInstance()
{
  static WallFactory instance;
  return instance;
}

std::uint32_t WallFactory::createWall(float positionX, float positionY, float width, float height,
                                      int drawOrder)
{
  if (width <= 0.0f || height <= 0.0f)
  {
    throw std::invalid_argument("WallFactory: width and height must be positive");
  }

  EntityManager& entityManager = EntityManager::getInstance();
  std::uint32_t wallEntityId = entityManager.createEntity();
  TransformComponent wallTransform{positionX, positionY, 0.0f, 1.0f};
  SpriteComponent wallSprite{0, drawOrder};
  entityManager.addTransformComponent(wallEntityId, wallTransform);
  entityManager.addSpriteComponent(wallEntityId, wallSprite);
  return wallEntityId;
}

std::uint32_t WallFactory::create()
{
  return createWall(100.0f, 100.0f, 32.0f, 32.0f, 2);
}
