#ifndef SPEED_COMPONENT_H
#define SPEED_COMPONENT_H

class SpeedComponent
{
  public:
    SpeedComponent() : speed(0.0f) {}
    explicit SpeedComponent(float speedValue) : speed(speedValue) {}
    float getSpeed() const { return speed; }
    void setSpeed(float speedValue) { speed = speedValue; }

  private:
    float speed;
};

#endif
