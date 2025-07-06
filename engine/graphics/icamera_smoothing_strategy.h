#pragma once
class ICameraSmoothingStrategy
{
  public:
    virtual ~ICameraSmoothingStrategy() = default;
    virtual void smoothCameraPosition(float& cameraPosX, float& cameraPosY, float targetPosX, float targetPosY,
                                      float deltaTime) = 0;
};
