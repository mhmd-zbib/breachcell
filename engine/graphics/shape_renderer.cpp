#include "shape_renderer.h"
#include "shape.h"
#include <cmath>

ShapeRenderer::ShapeRenderer(SDL_Renderer* rendererInstance) : renderer(rendererInstance) {}

void ShapeRenderer::drawFilledRect(int positionX, int positionY, int width, int height, unsigned char red,
                                   unsigned char green, unsigned char blue, unsigned char alpha)
{
    SDL_Rect rect = {positionX, positionY, width, height};
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

void ShapeRenderer::drawRectOutline(int positionX, int positionY, int width, int height, unsigned char red,
                                    unsigned char green, unsigned char blue, unsigned char alpha)
{
    SDL_Rect rect = {positionX, positionY, width, height};
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderDrawRect(renderer, &rect);
}

void ShapeRenderer::drawLine(int startX, int startY, int endX, int endY, unsigned char red, unsigned char green,
                             unsigned char blue, unsigned char alpha)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
}

void ShapeRenderer::drawCircle(int centerX, int centerY, int radius, unsigned char red, unsigned char green,
                               unsigned char blue, unsigned char alpha, ShapeStyle style)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    if (style == ShapeStyle::Filled)
    {
        for (int w = 0; w < radius * 2; w++)
        {
            for (int h = 0; h < radius * 2; h++)
            {
                int dx = radius - w;
                int dy = radius - h;
                if ((dx * dx + dy * dy) <= (radius * radius))
                    SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
    else
    {
        int segments = 360;
        for (int i = 0; i < segments; i++)
        {
            float theta1 = (float) i * 2.0f * 3.14159265f / segments;
            float theta2 = (float) (i + 1) * 2.0f * 3.14159265f / segments;
            int x1 = centerX + (int) (radius * cosf(theta1));
            int y1 = centerY + (int) (radius * sinf(theta1));
            int x2 = centerX + (int) (radius * cosf(theta2));
            int y2 = centerY + (int) (radius * sinf(theta2));
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
    }
}

void ShapeRenderer::drawShape(IShape* shape, ShapeStyle style)
{
    if (shape)
        shape->draw(this, style);
}
