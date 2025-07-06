#include "rectangle_shape.h"
#include "shape_renderer.h"

RectangleShape::RectangleShape(int positionX, int positionY, int width, int height, unsigned char red,
                               unsigned char green, unsigned char blue, unsigned char alpha)
    : positionX(positionX), positionY(positionY), width(width), height(height), red(red), green(green), blue(blue),
      alpha(alpha)
{
}

void RectangleShape::draw(ShapeRenderer* shapeRenderer, ShapeStyle style)
{
    if (style == ShapeStyle::Filled)
        shapeRenderer->drawFilledRect(positionX, positionY, width, height, red, green, blue, alpha);
    else
        shapeRenderer->drawRectOutline(positionX, positionY, width, height, red, green, blue, alpha);
}
