#include "ecs/entity_manager.h"
#include "factories/enemy_factory.h"
#include "factories/player_factory.h"
#include "factories/wall_factory.h"

EntityManager& EntityManager::getInstance() {
  static EntityManager instance;
  return instance;
}
EntityManager::EntityManager() : nextEntityId(1) {}
std::uint32_t EntityManager::createEntity() {
  return nextEntityId++;
}
void EntityManager::destroyEntity(std::uint32_t entityId) {
  transformComponents.erase(entityId);
  velocityComponents.erase(entityId);
  spriteComponents.erase(entityId);
  inputComponents.erase(entityId);
  projectileComponents.erase(entityId);
  healthComponents.erase(entityId);
  aimComponents.erase(entityId);
}
TransformComponent* EntityManager::getTransformComponent(std::uint32_t entityId) {
  auto it = transformComponents.find(entityId);

  if (it != transformComponents.end()) {
    return &it->second;
  }

  return nullptr;
}
VelocityComponent* EntityManager::getVelocityComponent(std::uint32_t entityId) {
  auto it = velocityComponents.find(entityId);

  if (it != velocityComponents.end()) {
    return &it->second;
  }

  return nullptr;
}
SpriteComponent* EntityManager::getSpriteComponent(std::uint32_t entityId) {
  auto it = spriteComponents.find(entityId);

  if (it != spriteComponents.end()) {
    return &it->second;
  }

  return nullptr;
}
InputComponent* EntityManager::getInputComponent(std::uint32_t entityId) {
  auto it = inputComponents.find(entityId);

  if (it != inputComponents.end()) {
    return &it->second;
  }

  return nullptr;
}
ProjectileComponent* EntityManager::getProjectileComponent(std::uint32_t entityId) {
  auto it = projectileComponents.find(entityId);

  if (it != projectileComponents.end()) {
    return &it->second;
  }

  return nullptr;
}
HealthComponent* EntityManager::getHealthComponent(std::uint32_t entityId) {
  auto it = healthComponents.find(entityId);

  if (it != healthComponents.end()) {
    return &it->second;
  }

  return nullptr;
}
AimComponent* EntityManager::getAimComponent(std::uint32_t entityId) {
  auto it = aimComponents.find(entityId);

  if (it != aimComponents.end()) {
    return &it->second;
  }

  return nullptr;
}
ShooterAimingProvider* EntityManager::getShooterAimingProvider(std::uint32_t entityId) {
  AimComponent* aim = getAimComponent(entityId);

  if (aim) {
    return aim;
  }

  return nullptr;
}
void EntityManager::addTransformComponent(std::uint32_t             entityId,
                                          const TransformComponent& component) {
  transformComponents[entityId] = component;
}
void EntityManager::addVelocityComponent(std::uint32_t            entityId,
                                         const VelocityComponent& component) {
  velocityComponents[entityId] = component;
}
void EntityManager::addSpriteComponent(std::uint32_t entityId, const SpriteComponent& component) {
  spriteComponents[entityId] = component;
}
void EntityManager::addInputComponent(std::uint32_t entityId, const InputComponent& component) {
  inputComponents[entityId] = component;
}
void EntityManager::addProjectileComponent(std::uint32_t              entityId,
                                           const ProjectileComponent& component) {
  projectileComponents[entityId] = component;
}
void EntityManager::addHealthComponent(std::uint32_t entityId, const HealthComponent& component) {
  healthComponents[entityId] = component;
}
void EntityManager::addComponent(std::uint32_t entityId, const AimComponent& component) {
  aimComponents[entityId] = component;
}
std::uint32_t EntityManager::createEntities() {
  std::uint32_t playerEntityId =
      PlayerFactory::getInstance().createPlayer(400.0f, 300.0f, 0.0f, 1.0f, 1, 0);
  EnemyFactory::getInstance().createEnemy(200.0f, 200.0f, 0.0f, 1.0f, 2, 1);
  WallFactory::getInstance().createWall(100.0f, 100.0f, 32.0f, 32.0f, 2);
  return playerEntityId;
}
