#include "point.hpp"

#include "cell.hpp"
#include "edge.hpp"

// LES METHODES

// Constructeurs et destructeur

Point::Point (real_t xval, real_t yval, real_t zval) : x (xval), y (yval), z (zval), points ({}), edges ({}), cells ({})
{
}

Point::Point (const Point &pointToCopy) :
    x (pointToCopy.x),
    y (pointToCopy.y),
    z (pointToCopy.z),
    points (pointToCopy.points),
    edges (pointToCopy.edges),
    cells (pointToCopy.cells)
{
}

// Opérations sur les points

Point &
Point::operator+= (const Point &b)
{
    x += b.x;
    y += b.y;
    z += b.z;
    return *this;
}

Point &
Point::operator-= (const Point &b)
{
    x -= b.x;
    y -= b.y;
    z -= b.z;
    return *this;
}

Point &
Point::operator*= (real_t k)
{
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

// LES FONCTIONS

Point
operator+ (const Point &a, const Point &b)
{
    Point res = a;
    res += b;
    return res;
}

Point
operator- (const Point &a, const Point &b)
{
    Point res = a;
    res -= b;
    return res;
}

Point
operator* (const Point &a, real_t k)
{
    Point res = a;
    res *= k;
    return res;
}

Point
operator* (real_t k, const Point &a)
{
    return a * k;
}
