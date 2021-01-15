#ifndef DELAUNAYMESH_HPP
#define DELAUNAYMESH_HPP

#include <array>
#include <cmath>
#include <vector>

#include "../orionglobal.hpp"
#include "edge.hpp"
#include "point.hpp"
#include "triangle.hpp"

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
    std::vector<real_t>   inradius;
    std::vector<real_t>   maxlength;
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

    std::vector<Edge> edges;

    void
    InsertEdge (idx_t idtri1, idx_t idtri2);

    void
    InsertEdge (Edge e);
};

void
BuildEdges (Mesh *mesh);

void
PurgeInvalids (Mesh *mesh);

void
EraseBox (Mesh *mesh);

void
PrintStatistics (Mesh *mesh, const char *name);
#endif  // DELAUNAYMESH_HPP
