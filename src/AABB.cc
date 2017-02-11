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

bool AABB::will_not_collide(const AABB & from, const Point & to) const
{
  AABB destination(to.y, to.x,
                   to.y + from.get_height(),
		   to.x + from.get_width());
  AABB collision_area = from.min_bounding_box(destination);

  return !intersect(collision_area);
}

bool AABB::collision_point(const AABB & from, const Point & to,
                           Point & where) const
{
  float current_x{static_cast<float>(from.get_left())};
  float current_y{static_cast<float>(from.get_top())};

  int x_dist{to.x - from.get_left()};
  int y_dist{to.y - from.get_top()};
  int long_dist{max(abs(x_dist), abs(y_dist))};

  float dx{static_cast<float>(x_dist) / long_dist};
  float dy{static_cast<float>(y_dist) / long_dist};
  for (int i{0}; i < long_dist; ++i)
  {
      current_x += dx;
      current_y += dy;
      int rounded_x{static_cast<int>(round(current_x))};
      int rounded_y{static_cast<int>(round(current_y))};

      AABB this_pos(rounded_y, rounded_x,
                    rounded_y + from.get_height(),
                    rounded_x + from.get_width());

      if (intersect(this_pos))
      {
          where.x = rounded_x;
          where.y = rounded_y;
          return true;
      }
  }
  return false;
}

AABB AABB::min_bounding_box(const AABB & a) const
{
  int new_left{min(left, a.get_left())};
  int new_top{min(top, a.get_top() )};
  int new_right{max(right, a.get_right())};
  int new_bottom{max(bottom, a.get_bottom())};
  AABB new_AABB(new_top, new_left, new_bottom, new_right);

  return new_AABB;
}

int AABB::get_width() const
{
  return (right - left);
}

int AABB::get_height() const
{
  return (bottom - top);
}

int AABB::get_left() const
{
  return left;
}

int AABB::get_right() const
{
  return right;
}

int AABB::get_top() const
{
  return top;
}

int AABB::get_bottom() const
{
  return bottom;
}
