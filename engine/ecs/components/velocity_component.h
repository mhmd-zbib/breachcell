#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

class VelocityComponent
{
  public:
    VelocityComponent(float velocityX = 0.0f, float velocityY = 0.0f);
    float getVelocityX() const;
    float getVelocityY() const;
    void setVelocityX(float velocityX);
    void setVelocityY(float velocityY);

  private:
    float velocityX;
    float velocityY;
};

#endif
