#include "circle_shape.h"
#include "shape_renderer.h"

CircleShape::CircleShape(int centerX, int centerY, int radius, unsigned char red, unsigned char green,
                         unsigned char blue, unsigned char alpha)
    : centerX(centerX), centerY(centerY), radius(radius), red(red), green(green), blue(blue), alpha(alpha)
{
}

void CircleShape::draw(ShapeRenderer* shapeRenderer, ShapeStyle style)
{
    shapeRenderer->drawCircle(centerX, centerY, radius, red, green, blue, alpha, style);
}
