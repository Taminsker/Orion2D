#ifndef POINT_HPP
#define POINT_HPP

#include "../orionglobal.hpp"

#include <array>
#include <cmath>

typedef std::array<real_t, 2> Point;  // real_t[2]

typedef enum
{
    INSIDE  = -1,
    BORDER  = 0,
    OUTSIDE = 1,
} LOC;


ORION_HARD_INLINE
real_t
Norm (const Point p)
{
    return std::sqrt (p [0] * p [0] + p [1] * p [1]);
}

ORION_HARD_INLINE
Point
operator+ (const Point &a, const Point &b)
{
    return {a [0] + b [0], a [1] + b [1]};
}

ORION_HARD_INLINE
Point
operator- (const Point &a, const Point &b)
{
    return {a [0] - b [0], a [1] - b [1]};
}

ORION_HARD_INLINE
Point
operator* (const real_t &k, const Point &a)
{
    return {k * a [0], k * a [1]};
}


#endif // POINT_HPP
