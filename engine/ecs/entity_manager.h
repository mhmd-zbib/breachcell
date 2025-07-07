#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <any>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum class EntityTag
{
    Player,
    Box
};

class EntityManager
{
  public:
    EntityManager();
    int createEntity(EntityTag tag);
    void destroyEntity(int entityId);
    bool isEntityAlive(int entityId) const;
    void reset();
    template <typename ComponentType> void addComponent(int entityId, ComponentType&& component)
    {
        std::unordered_map<int, std::any>& componentMap = componentStorage[std::type_index(typeid(ComponentType))];
        componentMap[entityId] = std::forward<ComponentType>(component);
    }
    template <typename ComponentType> ComponentType* getComponent(int entityId)
    {
        auto storageIt = componentStorage.find(std::type_index(typeid(ComponentType)));
        if (storageIt == componentStorage.end())
            return nullptr;
        auto& componentMap = storageIt->second;
        auto it = componentMap.find(entityId);
        if (it == componentMap.end())
            return nullptr;
        return std::any_cast<ComponentType>(&(it->second));
    }
    template <typename ComponentType> void removeComponent(int entityId)
    {
        auto storageIt = componentStorage.find(std::type_index(typeid(ComponentType)));
        if (storageIt == componentStorage.end())
            return;
        storageIt->second.erase(entityId);
    }
    EntityTag getTag(int entityId) const;
    int getEntityByTag(EntityTag tag) const;
    std::vector<int> getAllEntities() const { return std::vector<int>(activeEntities.begin(), activeEntities.end()); }

  private:
    int nextEntityId;
    std::unordered_set<int> activeEntities;
    std::unordered_map<std::type_index, std::unordered_map<int, std::any>> componentStorage;
    std::unordered_map<int, EntityTag> entityTags;
};

#endif
