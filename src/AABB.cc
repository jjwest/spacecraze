#include <cmath>
#include <algorithm>

#include "AABB.h"

using namespace std;

bool AABB::contain(int x, int y) const
{
  return (x <= right &&
          x >= left &&
          y <= bottom &&
          y >= top);
}

bool AABB::contain(const Point& a) const
{
  return (a.x <= right &&
          a.x >= left &&
          a.y <= bottom &&
          a.y >= top);
}

bool AABB::intersect(const AABB& a) const
{
  return (a.left <= right &&
          a.right >= left &&
          a.top <= bottom &&
          a.bottom >= top);
}

int AABB::width() const
{
  return right - left;
}

int AABB::height() const
{
  return bottom - top;
}
