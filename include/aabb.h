#ifndef AABB_H
#define AABB_H

#include "point.h"

class AABB
{
 public:
  AABB(int, int, int, int);
  AABB(const Point &, const Point &);
  bool contain(int, int) const;
  bool contain(const Point &) const;
  bool intersect(const AABB &) const;
  bool will_not_collide(const AABB &, const Point &) const;
  bool collision_point(const AABB &, const Point &, Point &) const;
  AABB min_bounding_box(const AABB &) const;
  int get_width() const;
  int get_height() const;
  int get_left() const;
  int get_right() const;
  int get_top() const;
  int get_bottom() const;

 private:
  int top, left, bottom, right;
};

#endif
