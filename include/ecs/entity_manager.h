#pragma once
#include <unordered_map>
#include <cstdint>
#include <memory>
#include "ecs/components.h"
class EntityManager
{
public:
  static EntityManager &getInstance();
  std::uint32_t createEntity();
  void destroyEntity(std::uint32_t entityId);
  TransformComponent *getTransformComponent(std::uint32_t entityId);
  VelocityComponent *getVelocityComponent(std::uint32_t entityId);
  SpriteComponent *getSpriteComponent(std::uint32_t entityId);
  InputComponent *getInputComponent(std::uint32_t entityId);
  ProjectileComponent *getProjectileComponent(std::uint32_t entityId);
  void addTransformComponent(std::uint32_t entityId, const TransformComponent &component);
  void addVelocityComponent(std::uint32_t entityId, const VelocityComponent &component);
  void addSpriteComponent(std::uint32_t entityId, const SpriteComponent &component);
  void addInputComponent(std::uint32_t entityId, const InputComponent &component);
  void addProjectileComponent(std::uint32_t entityId, const ProjectileComponent &component);
  static constexpr std::uint32_t MAX_ENTITY_ID = 1024;

private:
  EntityManager();
  std::uint32_t nextEntityId;
  std::unordered_map<std::uint32_t, TransformComponent> transformComponents;
  std::unordered_map<std::uint32_t, VelocityComponent> velocityComponents;
  std::unordered_map<std::uint32_t, SpriteComponent> spriteComponents;
  std::unordered_map<std::uint32_t, InputComponent> inputComponents;
  std::unordered_map<std::uint32_t, ProjectileComponent> projectileComponents;
};
