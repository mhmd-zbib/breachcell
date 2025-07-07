#include "texture_render_system.h"
#include "../components/texture_component.h"
#include <stdexcept>

TextureRenderSystem::TextureRenderSystem(TextureManager* manager) : textureManager(manager)
{
    if (!textureManager)
        throw std::invalid_argument("TextureManager pointer is null");
}

void TextureRenderSystem::render(EntityManager& entityManager, Renderer* renderer)
{
    if (!renderer)
        throw std::invalid_argument("Renderer pointer is null");
    for (int entityId : entityManager.getAllEntities())
    {
        TransformComponent* transform = entityManager.getComponent<TransformComponent>(entityId);
        TextureComponent* textureComponent = entityManager.getComponent<TextureComponent>(entityId);
        if (!transform || !textureComponent)
            continue;
        Texture* texture = textureManager->getTexture(textureComponent->getTextureId());
        if (!texture)
            throw std::runtime_error("TextureRenderSystem: Texture not found for entity " + std::to_string(entityId));
        renderer->drawTexture(*texture, static_cast<int>(transform->getPositionX()),
                              static_cast<int>(transform->getPositionY()));
    }
}
