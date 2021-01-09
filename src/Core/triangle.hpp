#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <array>
#include <iostream>

#include "../orionglobal.hpp"
#include "edge.hpp"
#include "point.hpp"

typedef std::array<idx_t, 3> Triangle;  // idx_t[3]

ORION_HARD_INLINE
void
InvalidThis (Triangle &triangle)
{
    triangle [0] = -1;
    return;
}

ORION_HARD_INLINE
bool
IsValid (Triangle &triangle)
{
    return triangle [0] > -1;
}

ORION_HARD_INLINE
bool
EdgeOnTriangle (Triangle &tri, Edge e)
{
    if (!IsValid (tri))
        return false;

    if (tri [0] == e [0] || tri [1] == e [0] || tri [2] == e [0])
        if (tri [0] == e [1] || tri [1] == e [1] || tri [2] == e [1])
            return true;

    return false;
}

ORION_HARD_INLINE
bool
PointOnTriangle (Triangle &tri, idx_t id)
{
    if (!IsValid (tri))
        return false;

    if (tri [0] == id || tri [1] == id || tri [2] == id)
        return true;

    return false;
}

ORION_HARD_INLINE
bool
SharedEdge (Triangle &tri1, Triangle &tri2, Edge *shared)
{
    *shared = {tri2 [0], tri2 [1], -1, -1};
    if (EdgeOnTriangle (tri1, *shared))
        return true;

    *shared = {tri2 [1], tri2 [2], -1, -1};
    if (EdgeOnTriangle (tri1, *shared))
        return true;

    *shared = {tri2 [0], tri2 [2], -1, -1};
    if (EdgeOnTriangle (tri1, *shared))
        return true;

    *shared = {-1, -1, -1, -1};
    return false;
}

ORION_HARD_INLINE
real_t
ComputeArea (Point &pA, Point &pB, Point &pC)
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Aire du triangle ABC = 0.5 * ||AB^AC|| = 0.5 * ||[0, 0, z_ABC]||
    // Composante z de AB^AC = u^v
    // Aire du triangle ABC (maille K)
    //
    /////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief u_AB
    ///
    Point u_AB = pB - pA;
    Point u_AC = pC - pA;

    real_t det = u_AB [0] * u_AC [1] - u_AB [1] * u_AC [0];

    return 0.5 * std::fabs (det);
}

#endif  // TRIANGLE_HPP