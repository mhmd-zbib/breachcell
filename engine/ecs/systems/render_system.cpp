#include "render_system.h"
#include "../components/box_component.h"
#include "../components/transform_component.h"
#include <vector>

RenderSystem::RenderSystem() {}

void RenderSystem::setCameraSystem(std::shared_ptr<CameraSystem> cameraSystemPtr)
{
    cameraSystem = cameraSystemPtr;
}

void RenderSystem::render(EntityManager& entityManager, Renderer* renderer)
{
    if (!cameraSystem)
        return;
    CameraComponent* camera = cameraSystem->getCameraComponent();
    float cameraX = camera->getPositionX();
    float cameraY = camera->getPositionY();
    for (int entityId : entityManager.getAllEntities())
    {
        TransformComponent* transform = entityManager.getComponent<TransformComponent>(entityId);
        if (!transform)
            continue;
        EntityTag tag = entityManager.getTag(entityId);
        if (tag == EntityTag::Player)
        {
            float screenX = transform->getPositionX() - cameraX;
            float screenY = transform->getPositionY() - cameraY;
            CircleShape circle((int) screenX, (int) screenY, 40, 0, 200, 255, 255);
            renderer->getShapeRenderer()->drawShape(&circle, ShapeStyle::Filled);
        }
        if (tag == EntityTag::Box)
        {
            BoxComponent* box = entityManager.getComponent<BoxComponent>(entityId);
            if (!box)
                continue;
            float screenX = transform->getPositionX() - cameraX;
            float screenY = transform->getPositionY() - cameraY;
            RectangleShape rect((int) screenX, (int) screenY, (int) box->getWidth(), (int) box->getHeight(),
                                box->getRed(), box->getGreen(), box->getBlue(), box->getAlpha());
            renderer->getShapeRenderer()->drawShape(&rect, ShapeStyle::Filled);
        }
    }
}
