#pragma once
#include <cstdint>
class IShootingSystem {
public:
  virtual ~IShootingSystem()                        = default;
  virtual void update(std::uint32_t playerEntityId) = 0;
};
class EntityManager;
class ProjectileFactory;
class ShootingSystem : public IShootingSystem {
public:
  ShootingSystem(EntityManager* entityManager, ProjectileFactory* projectileFactory);
  void update(std::uint32_t playerEntityId) override;

private:
  EntityManager*         entityManager;
  ProjectileFactory*     projectileFactory;
  static constexpr float PROJECTILE_SPEED = 400.0f;
};
