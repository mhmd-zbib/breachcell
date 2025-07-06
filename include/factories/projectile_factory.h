#pragma once
#include "ecs/entity_manager.h"
#include <cstdint>
#include <string>
class ProjectileFactory : public IEntityFactory
{
public:
  static ProjectileFactory& getInstance();
  std::uint32_t create() override;
  std::uint32_t createProjectile(float positionX, float positionY, float velocityX, float velocityY,
                                 float width, float height, float lifetime,
                                 const std::string& textureId, std::uint32_t ownerId);

private:
  ProjectileFactory();
  ProjectileFactory(const ProjectileFactory&) = delete;
  ProjectileFactory& operator=(const ProjectileFactory&) = delete;
  void validateParameters(float positionX, float positionY, float velocityX, float velocityY,
                          float width, float height, float lifetime, const std::string& textureId);
};
