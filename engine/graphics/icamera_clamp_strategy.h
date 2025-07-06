#pragma once
class ICameraClampStrategy
{
  public:
    virtual ~ICameraClampStrategy() = default;
    virtual void clampCameraPosition(float& cameraPosX, float& cameraPosY, float viewportWidth,
                                     float viewportHeight) = 0;
};
