#include "ecs/entity_manager.h"
EntityManager &EntityManager::getInstance()
{
  static EntityManager instance;
  return instance;
}
EntityManager::EntityManager() : nextEntityId(1) {}
std::uint32_t EntityManager::createEntity()
{
  return nextEntityId++;
}
void EntityManager::destroyEntity(std::uint32_t entityId)
{
  transformComponents.erase(entityId);
  velocityComponents.erase(entityId);
  spriteComponents.erase(entityId);
  inputComponents.erase(entityId);
}
TransformComponent *EntityManager::getTransformComponent(std::uint32_t entityId)
{
  auto it = transformComponents.find(entityId);
  if (it != transformComponents.end())
    return &it->second;
  return nullptr;
}
VelocityComponent *EntityManager::getVelocityComponent(std::uint32_t entityId)
{
  auto it = velocityComponents.find(entityId);
  if (it != velocityComponents.end())
    return &it->second;
  return nullptr;
}
SpriteComponent *EntityManager::getSpriteComponent(std::uint32_t entityId)
{
  auto it = spriteComponents.find(entityId);
  if (it != spriteComponents.end())
    return &it->second;
  return nullptr;
}
InputComponent *EntityManager::getInputComponent(std::uint32_t entityId)
{
  auto it = inputComponents.find(entityId);
  if (it != inputComponents.end())
    return &it->second;
  return nullptr;
}
void EntityManager::addTransformComponent(std::uint32_t entityId, const TransformComponent &component)
{
  transformComponents[entityId] = component;
}
void EntityManager::addVelocityComponent(std::uint32_t entityId, const VelocityComponent &component)
{
  velocityComponents[entityId] = component;
}
void EntityManager::addSpriteComponent(std::uint32_t entityId, const SpriteComponent &component)
{
  spriteComponents[entityId] = component;
}
void EntityManager::addInputComponent(std::uint32_t entityId, const InputComponent &component)
{
  inputComponents[entityId] = component;
}
