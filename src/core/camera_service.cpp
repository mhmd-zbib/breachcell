#include "core/camera_service.h"
#include <stdexcept>

CameraService::CameraService() : targetEntityId(-1) {
  viewRectangle = {0, 0, 800, 600};
}

void CameraService::setTargetEntityId(int targetEntityId) {
  if (targetEntityId < 0) {
    throw std::invalid_argument("Invalid entity id");
  }

  this->targetEntityId = targetEntityId;
}

void CameraService::updateCameraPosition(int targetPositionX, int targetPositionY, int screenWidth,
                                         int screenHeight) {
  viewRectangle.x = targetPositionX - screenWidth / 2;
  viewRectangle.y = targetPositionY - screenHeight / 2;
  viewRectangle.w = screenWidth;
  viewRectangle.h = screenHeight;
}

SDL_Rect CameraService::getViewRectangle() const {
  return viewRectangle;
}
