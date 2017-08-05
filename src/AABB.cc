#include <cmath>
#include <algorithm>

#include "AABB.h"

using namespace std;

AABB::AABB(int t, int l, int b, int r)
  : top{min(t, b)}, left{min(l, r)}, bottom{max(b, t)}, right{max(r, l)}{}

AABB::AABB(const Point & a, const Point & b) :
  top{ min(a.y, b.y) },
  left{ min(a.x, b.x) },
  bottom { max(a.y, b.y) },
  right{ max(a.x, b.x) } {}

bool AABB::contain(int x, int y) const
{
  return (x <= right &&
          x >= left &&
          y <= bottom &&
          y >= top);
}

bool AABB::contain(const Point & a) const
{
  return (a.x <= right &&
          a.x >= left &&
          a.y <= bottom &&
          a.y >= top);
}

bool AABB::intersect(const AABB & a) const
{
  return (a.left <= right &&
          a.right >= left &&
          a.top <= bottom &&
          a.bottom >= top);
}

bool AABB::willNotCollide(const AABB & from, const Point & to) const
{
  AABB destination(to.y, to.x,
                   to.y + from.getHeight(),
		   to.x + from.getWidth());
  AABB collision_area = from.minBoundingBox(destination);

  return !intersect(collision_area);
}

bool AABB::collisionPoint(const AABB & from, const Point & to,
                           Point & where) const
{
  float current_x{static_cast<float>(from.getLeft())};
  float current_y{static_cast<float>(from.getTop())};

  int x_distance{to.x - from.getLeft()};
  int y_distance{to.y - from.getTop()};
  int longest_distance{max(abs(x_distance), abs(y_distance))};

  float dx{static_cast<float>(x_distance) / longest_distance};
  float dy{static_cast<float>(y_distance) / longest_distance};

  for (int i{0}; i < longest_distance; ++i)
  {
      current_x += dx;
      current_y += dy;
      int rounded_x{static_cast<int>(round(current_x))};
      int rounded_y{static_cast<int>(round(current_y))};

      AABB this_pos(rounded_y, rounded_x,
                    rounded_y + from.getHeight(),
                    rounded_x + from.getWidth());

      if (intersect(this_pos))
      {
          where.x = rounded_x;
          where.y = rounded_y;
          return true;
      }
  }
  return false;
}

AABB AABB::minBoundingBox(const AABB & a) const
{
  int new_left{min(left, a.getLeft())};
  int new_top{min(top, a.getTop() )};
  int new_right{max(right, a.getRight())};
  int new_bottom{max(bottom, a.getBottom())};
  AABB new_AABB(new_top, new_left, new_bottom, new_right);

  return new_AABB;
}

int AABB::getWidth() const
{
  return (right - left);
}

int AABB::getHeight() const
{
  return (bottom - top);
}

int AABB::getLeft() const
{
  return left;
}

int AABB::getRight() const
{
  return right;
}

int AABB::getTop() const
{
  return top;
}

int AABB::getBottom() const
{
  return bottom;
}
