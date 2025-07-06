#ifndef CIRCLE_SHAPE_H
#define CIRCLE_SHAPE_H

#include "shape.h"

class CircleShape : public IShape
{
  public:
    CircleShape(int centerX, int centerY, int radius, unsigned char red, unsigned char green, unsigned char blue,
                unsigned char alpha = 255);
    void draw(ShapeRenderer* shapeRenderer, ShapeStyle style) override;

  private:
    int centerX;
    int centerY;
    int radius;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

#endif
