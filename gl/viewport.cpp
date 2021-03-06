#include "viewport.h"
#include "cgl.h"

using namespace cgl;

Viewport::Viewport() : x(0), y(0), width(1), height(1)
{
}

Viewport::Viewport(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height)
{
}

float Viewport::aspect() const
{
  return (float)width/height;
}

void Viewport::apply() const
{
  glViewport(x, y, width, height);
}

bool Viewport::operator==(const Viewport& v) const
{
  return (x == v.x && y == v.y && width == v.width && height == v.height);
}

bool Viewport::operator!=(const Viewport& v) const
{
  return (x != v.x || y != v.y || width != v.width || height != v.height);
}
