#pragma once
#include <cstdint>
class IHealthSystem {
public:
  virtual ~IHealthSystem() = default;
  virtual void update()    = 0;
};
class EntityManager;
class HealthSystem : public IHealthSystem {
public:
  HealthSystem(EntityManager* entityManager);
  void update() override;

private:
  EntityManager* entityManager;
};
