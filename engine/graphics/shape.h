#ifndef ISHAPE_H
#define ISHAPE_H

enum class ShapeStyle
{
    Outline,
    Filled
};

class ShapeRenderer;

class IShape
{
  public:
    virtual void draw(ShapeRenderer* shapeRenderer, ShapeStyle style) = 0;
    virtual ~IShape() = default;
};

#endif
