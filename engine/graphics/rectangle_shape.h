#ifndef RECTANGLE_SHAPE_H
#define RECTANGLE_SHAPE_H

#include "shape.h"

class RectangleShape : public IShape
{
  public:
    RectangleShape(int positionX, int positionY, int width, int height, unsigned char red, unsigned char green,
                   unsigned char blue, unsigned char alpha = 255);
    void draw(ShapeRenderer* shapeRenderer, ShapeStyle style) override;

  private:
    int positionX;
    int positionY;
    int width;
    int height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

#endif
