#ifndef AABB_H
#define AABB_H

#include "Point.h"

struct AABB
{
    int top, left, bottom, right;

    bool contain(int, int) const;
    bool contain(const Point &) const;
    bool intersect(const AABB &) const;
    int width() const;
    int height() const;
};

#endif
