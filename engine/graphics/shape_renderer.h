#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include "shape.h"
#include <SDL2/SDL.h>

class IShape;

class ShapeRenderer
{
  public:
    ShapeRenderer(SDL_Renderer* rendererInstance);
    void drawFilledRect(int positionX, int positionY, int width, int height, unsigned char red, unsigned char green,
                        unsigned char blue, unsigned char alpha = 255);
    void drawRectOutline(int positionX, int positionY, int width, int height, unsigned char red, unsigned char green,
                         unsigned char blue, unsigned char alpha = 255);
    void drawLine(int startX, int startY, int endX, int endY, unsigned char red, unsigned char green,
                  unsigned char blue, unsigned char alpha = 255);
    void drawCircle(int centerX, int centerY, int radius, unsigned char red, unsigned char green, unsigned char blue,
                    unsigned char alpha, ShapeStyle style);
    void drawShape(IShape* shape, ShapeStyle style);

  private:
    SDL_Renderer* renderer;
};

#endif
