#include "entity_manager.h"
#include <any>
#include <typeindex>

EntityManager::EntityManager() : nextEntityId(1) {}

int EntityManager::createEntity(EntityTag tag)
{
    int entityId = nextEntityId++;
    activeEntities.insert(entityId);
    entityTags[entityId] = tag;
    return entityId;
}

void EntityManager::destroyEntity(int entityId)
{
    activeEntities.erase(entityId);
    for (auto& [typeIdx, componentMap] : componentStorage)
    {
        componentMap.erase(entityId);
    }
    entityTags.erase(entityId);
}

bool EntityManager::isEntityAlive(int entityId) const
{
    return activeEntities.find(entityId) != activeEntities.end();
}

void EntityManager::reset()
{
    nextEntityId = 1;
    activeEntities.clear();
    componentStorage.clear();
    entityTags.clear();
}

EntityTag EntityManager::getTag(int entityId) const
{
    auto it = entityTags.find(entityId);
    if (it != entityTags.end())
        return it->second;
    return static_cast<EntityTag>(-1);
}

int EntityManager::getEntityByTag(EntityTag tag) const
{
    for (const auto& [id, t] : entityTags)
    {
        if (t == tag)
            return id;
    }
    return -1;
}
