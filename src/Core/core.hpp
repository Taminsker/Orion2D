#ifndef CORE_HPP
#define CORE_HPP

#include <array>
#include <cmath>
#include <vector>

#include "../orionglobal.hpp"

typedef std::array<real_t, 2> Point;
typedef std::array<idx_t, 3>  Triangle;
typedef std::array<idx_t, 2>  Edge;

typedef enum
{
    INSIDE  = -1,
    BORDER  = 0,
    OUTSIDE = 1,
} LOC;

struct Mesh
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Points part
    //
    /////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Point> points;
    std::vector<LOC>   tagpoints;

    Point &
    InsertPoint (Point &point);

    Point &
    InsertPoint (real_t x, real_t y);

    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Cells parts
    //
    /////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<Triangle> triangles;
    std::vector<real_t>   areas;
    std::vector<Point>    circumcenters;
    std::vector<Point>    masscenters;
    std::vector<real_t>   radius;
    std::vector<real_t>   qualities;

    void
    InsertTriangle (idx_t i, idx_t j, idx_t k);

    void
    UpdateTriangle (ul_t id);

    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Edges part
    //
    /////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Edge> edgesbytriangles, edgesbypoints;

    void
    InsertEdgeByPoint (idx_t i, idx_t j);

    void
    InsertEdgeByPoint (Edge e);

    void
    InsertEdgeByTriangle (idx_t i, idx_t j);

    void
    InsertEdgeByTriangle (Edge e);
};

void
BuildEdges (Mesh *mesh);

void
PurgeInvalids (Mesh *mesh);

void
PrintStatistics (Mesh *mesh, const char *name);

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
    return triangle [0] != -1;
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
SharedEdge (Triangle &tri1, Triangle &tri2)
{
    if (EdgeOnTriangle (tri1, {tri2 [0], tri2 [1]}))
        return true;

    if (EdgeOnTriangle (tri1, {tri2 [1], tri2 [2]}))
        return true;

    if (EdgeOnTriangle (tri1, {tri2 [0], tri2 [2]}))
        return true;

    return false;
}

ORION_HARD_INLINE real_t
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
#endif  // CORE_HPP
