#include "core.hpp"

#include <iomanip>
#include <iostream>

Point &
Mesh::InsertPoint (Point &point)
{
    points.push_back ({point [0], point [1]});
    return points.back ();
}

Point &
Mesh::InsertPoint (real_t x, real_t y)
{
    points.push_back ({x, y});
    return points.back ();
}

void
Mesh::InsertTriangle (idx_t i, idx_t j, idx_t k)
{
    Triangle nc;
    nc [0] = std::min (std::min (i, j), k);
    nc [2] = std::max (std::max (i, j), k);
    nc [1] = i + j + k - nc [0] - nc [2];

    triangles.push_back (nc);

    Point circumcenter = {0, 0};
    Point masscenter   = {0, 0};

    areas.push_back (0);
    circumcenters.push_back (circumcenter);
    masscenters.push_back (masscenter);
    radius.push_back (0);
    qualities.push_back (0);

    return UpdateTriangle (triangles.size () - 1);
}

void
Mesh::UpdateTriangle (ul_t id)
{
    Triangle &tri = triangles [id];

    Point &pA = points [static_cast<ul_t> (tri [0])];
    Point &pB = points [static_cast<ul_t> (tri [1])];
    Point &pC = points [static_cast<ul_t> (tri [2])];

    Point u_AB = pB - pA;
    Point u_AC = pC - pA;
    Point u_BC = pC - pB;

    real_t dAB = Norm (u_AB);
    real_t dAC = Norm (u_AC);
    real_t dBC = Norm (u_BC);

    real_t sum = dAB * dAB + dAC * dAC + dBC * dBC;

    real_t det = u_AB [0] * u_AC [1] - u_AB [1] * u_AC [0];

    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Aire du triangle ABC = 0.5 * ||AB^AC|| = 0.5 * ||[0, 0, z_ABC]||
    // Composante z de AB^AC = u^v
    // Aire du triangle ABC (maille K)
    //
    /////////////////////////////////////////////////////////////////////////////////////////////
    areas [id] = 0.5 * std::fabs (det);

    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Circumcenter
    //
    /////////////////////////////////////////////////////////////////////////////////////////////
    real_t f = u_AB [0] * ((pA [0] + pB [0]) / 2.) + u_AB [1] * ((pA [1] + pB [1]) / 2.);
    real_t g = u_AC [0] * ((pA [0] + pC [0]) / 2.) + u_AC [1] * ((pA [1] + pC [1]) / 2.);

    circumcenters [id][0] = (u_AC [1] * f - u_AB [1] * g) / det;
    circumcenters [id][1] = (u_AB [0] * g - u_AC [0] * f) / det;

    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Radius
    //
    /////////////////////////////////////////////////////////////////////////////////////////////
    radius [id] = Norm (pA - circumcenters [id]);

    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Quality
    //
    /////////////////////////////////////////////////////////////////////////////////////////////
    qualities [id] = (MATH_SQRT3 / (12.0 * areas [id])) * sum;

    /////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Mass center
    //
    /////////////////////////////////////////////////////////////////////////////////////////////
    masscenters [id][0] = (pA [0] + pB [0] + pC [0]) / 3.;
    masscenters [id][1] = (pA [1] + pB [1] + pC [1]) / 3.;

    return;
}

void
Mesh::InsertEdge (idx_t i, idx_t j)
{
    Edge ne;
    ne [0] = std::min (i, j);
    ne [1] = std::max (i, j);

    edges.push_back (ne);

    return;
}

void
PurgeInvalids (Mesh *mesh)
{
    ul_t numTriangles = mesh->triangles.size ();

    ul_t cursor = 0;
    for (ul_t id = 0; id < numTriangles; ++id)
        if (IsValid (mesh->triangles [id]))
        {
            mesh->triangles [cursor]     = mesh->triangles [id];
            mesh->areas [cursor]         = mesh->areas [id];
            mesh->circumcenters [cursor] = mesh->circumcenters [id];
            mesh->masscenters [cursor]   = mesh->masscenters [id];
            mesh->radius [cursor]        = mesh->radius [id];
            mesh->qualities [cursor]     = mesh->qualities [id];

            cursor++;
        }

    mesh->triangles.resize (cursor);
    mesh->areas.resize (cursor);
    mesh->circumcenters.resize (cursor);
    mesh->masscenters.resize (cursor);
    mesh->radius.resize (cursor);
    mesh->qualities.resize (cursor);

    return;
}

void
PrintStatistics (Mesh *mesh, const char *name)
{
    BEGIN << "Mesh stats " << name << ENDLINE;
    INFOS << " Number of points : " << mesh->points.size () << ENDLINE;
    INFOS << " Number of edges  : " << mesh->edges.size () << ENDLINE;
    INFOS << " Number of triangles  : " << mesh->triangles.size () << ENDLINE;

    ENDFUN;
    return;
}
