#pragma once
#include <cstdint>
class IEntityFactory {
public:
  virtual ~IEntityFactory()      = default;
  virtual std::uint32_t create() = 0;
};
class EntityManager;
class WallFactory : public IEntityFactory {
public:
  WallFactory(EntityManager* entityManager);
  std::uint32_t create() override;

private:
  EntityManager* entityManager;
};
