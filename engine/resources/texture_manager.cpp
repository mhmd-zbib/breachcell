#include "texture_manager.h"
#include <stdexcept>

TextureManager::TextureManager(SDL_Renderer* sdlRenderer) : renderer(sdlRenderer), nextId(1)
{
    if (!renderer)
        throw std::invalid_argument("SDL_Renderer pointer is null");
}

int TextureManager::loadTexture(const std::string& textureKey, const std::string& filePath)
{

    if (textureKey.empty())
        throw std::invalid_argument("Texture key is empty");
    if (filePath.empty())
        throw std::invalid_argument("Texture file path is empty");
    if (keyToIdMap.count(textureKey))
        return keyToIdMap[textureKey];
    auto texture = std::make_unique<Texture>(renderer, filePath);
    if (!texture || texture->getNativeTexture() == nullptr)
        throw std::runtime_error("Failed to load texture: " + filePath);
    int id = nextId++;
    textureMap[id] = std::move(texture);
    keyToIdMap[textureKey] = id;
    return id;
}

Texture* TextureManager::getTexture(int textureId) const
{
    if (textureId <= 0)
        throw std::invalid_argument("Texture id must be positive");
    auto it = textureMap.find(textureId);
    if (it == textureMap.end())
        return nullptr;
    return it->second.get();
}

void TextureManager::unloadTexture(int textureId)
{
    if (textureId <= 0)
        throw std::invalid_argument("Texture id must be positive");
    for (auto it = keyToIdMap.begin(); it != keyToIdMap.end();)
    {
        if (it->second == textureId)
            it = keyToIdMap.erase(it);
        else
            ++it;
    }
    textureMap.erase(textureId);
}

void TextureManager::clear()
{
    keyToIdMap.clear();
    textureMap.clear();
    nextId = 1;
}
