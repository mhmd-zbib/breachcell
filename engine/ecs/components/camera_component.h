#pragma once
class CameraComponent
{
  public:
    CameraComponent();
    void setPosition(float positionX, float positionY);
    void setZoom(float zoomLevel);
    void setRotation(float angle);
    float getPositionX() const;
    float getPositionY() const;
    float getZoom() const;
    float getRotation() const;

  private:
    float positionX;
    float positionY;
    float zoom;
    float rotation;
};
