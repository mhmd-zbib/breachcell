#ifndef BOX_COMPONENT_H
#define BOX_COMPONENT_H

class BoxComponent
{
  public:
    BoxComponent(float width, float height, unsigned char red, unsigned char green, unsigned char blue,
                 unsigned char alpha = 255);
    float getWidth() const;
    float getHeight() const;
    unsigned char getRed() const;
    unsigned char getGreen() const;
    unsigned char getBlue() const;
    unsigned char getAlpha() const;

  private:
    float width;
    float height;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

#endif
