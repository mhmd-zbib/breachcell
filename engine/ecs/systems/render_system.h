#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "../../graphics/circle_shape.h"
#include "../../graphics/rectangle_shape.h"
#include "../../graphics/renderer.h"
#include "../../graphics/shape_renderer.h"
#include "../entity_manager.h"
#include "camera_system.h"

class RenderSystem
{
  public:
    RenderSystem();
    void setCameraSystem(std::shared_ptr<CameraSystem> cameraSystemPtr);
    void render(EntityManager& entityManager, Renderer* renderer);

  private:
    std::shared_ptr<CameraSystem> cameraSystem;
};

#endif
