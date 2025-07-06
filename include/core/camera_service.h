#pragma once
#include <SDL2/SDL.h>
#include <memory>

class CameraService
{
public:
  static CameraService& getInstance();
  void setTargetEntityId(int targetEntityId);
  void updateCameraPosition(int targetPositionX, int targetPositionY, int screenWidth,
                            int screenHeight);
  SDL_Rect getViewRectangle() const;

private:
  CameraService();
  int targetEntityId;
  SDL_Rect viewRectangle;
};
