#include "texture_render_system.h"
#include "../components/camera_component.h"
#include "../components/texture_component.h"
#include "../systems/camera_system.h"
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
    std::shared_ptr<CameraSystem> cameraSystem = renderer->getCameraSystem();
    CameraComponent* camera = cameraSystem ? cameraSystem->getCameraComponent() : nullptr;
    float cameraX = camera ? camera->getPositionX() : 0.0f;
    float cameraY = camera ? camera->getPositionY() : 0.0f;
    for (int entityId : entityManager.getAllEntities())
    {
        TransformComponent* transform = entityManager.getComponent<TransformComponent>(entityId);
        TextureComponent* textureComponent = entityManager.getComponent<TextureComponent>(entityId);
        if (!transform || !textureComponent)
            continue;
        Texture* texture = textureManager->getTexture(textureComponent->getTextureId());
        if (!texture)
            throw std::runtime_error("TextureRenderSystem: Texture not found for entity " + std::to_string(entityId));
        double rotationAngle = static_cast<double>(transform->getRotation());
        int drawX = static_cast<int>(transform->getPositionX() - cameraX);
        int drawY = static_cast<int>(transform->getPositionY() - cameraY);
        try
        {
            renderer->drawTexture(*texture, drawX, drawY, texture->getWidth(), texture->getHeight(), rotationAngle,
                                  SDL_FLIP_NONE, nullptr, 255);
        }
        catch (const std::exception& ex)
        {
            std::fprintf(stderr, "TextureRenderSystem: Render failed for entity %d: %s\n", entityId, ex.what());
        }
    }
}
