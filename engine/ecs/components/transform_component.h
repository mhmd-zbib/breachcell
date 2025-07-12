#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

class TransformComponent
{
  public:
    TransformComponent(float positionX = 0.0f, float positionY = 0.0f, float rotation = 0.0f);
    float getPositionX() const;
    float getPositionY() const;
    void setPositionX(float positionX);
    void setPositionY(float positionY);
    float getRotation() const;
    void setRotation(float rotation);

  private:
    float positionX;
    float positionY;
    float rotation;
};

#endif
