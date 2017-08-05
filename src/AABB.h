#ifndef AABB_H
#define AABB_H

#include "Point.h"

class AABB
{
 public:
  AABB(int, int, int, int);
  AABB(const Point &, const Point &);
  bool contain(int, int) const;
  bool contain(const Point &) const;
  bool intersect(const AABB &) const;
  bool willNotCollide(const AABB &, const Point &) const;
  bool collisionPoint(const AABB &, const Point &, Point &) const;
  AABB minBoundingBox(const AABB &) const;
  int getWidth() const;
  int getHeight() const;
  int getLeft() const;
  int getRight() const;
  int getTop() const;
  int getBottom() const;

 private:
  int top, left, bottom, right;
};

#endif
