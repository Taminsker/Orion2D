#include "delaunay.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>

// Pour savoir si le point p est dans le cercle circonscrit à la cellule edge
bool
PointInCircle (Mesh *mesh, Point &p, ul_t id)
{
    if (!IsValid (mesh->triangles [id]))
        return false;

    Point & center = mesh->circumcenters [id];
    real_t &radius = mesh->radius [id];

    if (Norm (p - center) < radius - 1E-10)
        return true;

    return false;
}

// bool
// PointInTriangle (Mesh *mesh, Point &p, ul_t id)
// {
//     if (!IsValid (mesh->triangles [id]))
//         return false;
//
//     Triangle &tri  = mesh->triangles [id];
//     // real_t    area = mesh->areas [id];
//
//     Point &pA = mesh->points [static_cast<ul_t> (tri [0])];
//     Point &pB = mesh->points [static_cast<ul_t> (tri [1])];
//     Point &pC = mesh->points [static_cast<ul_t> (tri [2])];
//
//     real_t area = 1./2. * (-pB[1] * pC[0] + pA[0] * (-pB[0] + pC[0]) + pA[0] * (pB[1] - pC[1]) + pB[0] * pC[1]);
//     //
//     int    sign = area < 0 ? -1 : 1;
//     // real_t s    = (pA [1] * pC [0] - pA [0] * pC [1] + (pC [1] - pA [1]) * p [0] + (pA [0] - pC [0]) * p [1]) *
//     sign;
//     // real_t t    = (pA [0] * pB [1] - pA [1] * pB [0] + (pA [1] - pB [1]) * p [0] + (pB [0] - pA [0]) * p [1]) *
//     sign;
//     //
//     // return s > 0 && t > 0 && (s + t) < 2 * area * sign;
//
//     Point u = pB - pA;
//     Point v = p - pA;
//     if (u[0] * v[1] - u[1] * v[0] < 0)
//         return false;
//
//     u = pC - pB;
//     v = p - pA;
//     if (u[0] * v[1] - u[1] * v[0] < 0)
//         return false;
//
//     u = pA - pC;
//     v = p - pB;
//     if (u[0] * v[1] - u[1] * v[0] < 0)
//         return false;
//
//     return true;
// }

void
DelaunayKernel (Point &p, Mesh *output)
{
    output->InsertPoint (p);

    ul_t numTriangles = output->triangles.size ();
    int  idInserted   = static_cast<int> (output->points.size ()) - 1;

    std::vector<Edge> edges;

    for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
        if (PointInCircle (output, p, idTri))
        {
            Triangle &tri = output->triangles [idTri];
            edges.insert (std::end (edges),
                          {{tri [0], tri [1], -1, -1}, {tri [1], tri [2], -1, -1}, {tri [0], tri [2], -1, -1}});

            InvalidThis (tri);
        }

    for (Edge &e : edges)
    {
        bool refound = false;
        for (Edge &ne : edges)
            if (e [0] == ne [0] && e [1] == ne [1] && &ne != &e)
            {
                refound = true;
                break;
            }

        if (!refound)
            output->InsertTriangle (idInserted, e [0], e [1]);
    }

    return;
}

void
DelaunayTriangulation (Mesh *input, Mesh *output)
{
    BEGIN << "Delaunay triangulation" << ENDLINE;

    ul_t numPoints = input->points.size ();

    if (numPoints == 0)
        return;

    output->points.reserve (2 * numPoints);
    output->tagpoints.reserve (2 * numPoints);
    output->triangles.reserve (4 * numPoints);
    output->areas.reserve (4 * numPoints);
    output->circumcenters.reserve (4 * numPoints);
    output->inradius.reserve (4 * numPoints);
    output->masscenters.reserve (4 * numPoints);
    output->radius.reserve (4 * numPoints);
    output->qualities.reserve (4 * numPoints);

    Point minp, maxp;
    minp [0] = maxp [0] = input->points [0][0];
    minp [1] = maxp [1] = input->points [0][1];

    for (Point &p : input->points)
    {
        maxp [0] = std::max (maxp [0], p [0]);
        maxp [1] = std::max (maxp [1], p [1]);

        minp [0] = std::min (minp [0], p [0]);
        minp [1] = std::min (minp [1], p [1]);
    }

    real_t eps = std::max (maxp [0] - minp [0], maxp [1] - minp [1]) * 0.7;  // add a box of 20% of the size

    minp [0] -= eps;
    minp [1] -= eps;
    maxp [0] += eps;
    maxp [1] += eps;

    // Points box
    output->InsertPoint (minp);                // bottom left
    output->InsertPoint (maxp [0], minp [1]);  // bottom right
    output->InsertPoint (minp [0], maxp [1]);  // top left
    output->InsertPoint (maxp);                // top right

    // Cells
    output->InsertTriangle (0, 1, 2);
    output->InsertTriangle (1, 2, 3);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Insert existing points
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (Point &p : input->points)
        DelaunayKernel (p, output);

    INFOS << "Added : " << numPoints << " points !" << ENDLINE;

    PurgeInvalids (output);
    INFOS << "Purge invalids ! " << ENDLINE;

    STATUS << "Done !" << ENDLINE;

    ENDFUN;
}

void
CheckDelaunayCriterion (Mesh *mesh)
{
    BEGIN << "Check Delaunay criterion" << ENDLINE;

    bool myboolean    = true;
    ul_t numPoints    = mesh->points.size ();
    ul_t numTriangles = mesh->triangles.size ();

    for (ul_t idPoint = 0; idPoint < numPoints; ++idPoint)
        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
            if (!PointOnTriangle (mesh->triangles [idTri], static_cast<idx_t> (idPoint)))
                if (PointInCircle (mesh, mesh->points [idPoint], idTri))
                {
                    Point &p = mesh->points [idPoint];
                    //                    Triangle &tri = mesh->triangles [idTri];

                    //                    ERROR << "The point " << idPoint << " [" << p [0] << " " << p [1] << "] in
                    //                    triangle " << idTri
                    //                          << "  " << tri [0] << " " << tri [1] << " " << tri [2] << ENDLINE;

                    ERROR << " criterion : [p = " << idPoint << " & tri = " << idTri
                          << "] ||p-c|| = " << Norm (p - mesh->circumcenters [idTri]) << " r = " << mesh->radius [idTri]
                          << " bool = " << (Norm (p - mesh->circumcenters [idTri]) < mesh->radius [idTri]) << ENDLINE;
                    myboolean = false;
                }

    if (myboolean)
        INFOS << "Everything is good ! " << ENDLINE;
    else
        ERROR << "An error occures..." << ENDLINE;

    STATUS << "Done !" << ENDLINE;
    ENDFUN;

    return;
}

void
InsertMasscenter (Mesh *input, Mesh *output, ul_t maxiter)
{
    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //    //
    //    // Insert masscenters
    //    //
    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    real_t distmax = Norm (input->points [static_cast<ul_t> (input->edges [0][0])] -
                           input->points [static_cast<ul_t> (input->edges [0][1])]);

    for (Edge &e : input->edges)
        distmax = std::max (
            distmax, Norm (input->points [static_cast<ul_t> (e [0])] - input->points [static_cast<ul_t> (e [1])]));

    bool myboolean      = true;
    ul_t count_loop     = 0;
    ul_t count_inserted = 0;

    while (myboolean && count_loop < maxiter)
    {
        myboolean = false;
        count_loop++;

        ul_t numTriangles = output->triangles.size ();
        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
        {
            if (IsValid (output->triangles [idTri]) && output->areas [idTri] > (distmax * distmax / 1.5) &&
                output->inradius [idTri] > 0.1 * distmax)
            {
                /////////////////////////////////////////////////////////////////////////////////////////////
                Point &p = output->circumcenters [idTri];
                /////////////////////////////////////////////////////////////////////////////////////////////

                //                if (p [0] < minp [0] || p [0] > maxp [0] || p [1] < minp [1] || p [1] > maxp [1])
                //                continue;
                //
                // if (!PointInTriangle (output, p, idTri))
                // {
                //     ERROR << "You try to add the point " << p[0] << " " << p[1] << " in triangle " << idTri <<
                //                ". But
                //     failed." << ENDLINE; ERROR << output->points[output->triangles[idTri][0]][0] << " " <<
                //     output->points[output->triangles[idTri][0]][1] << ENDLINE; ERROR <<
                //     output->points[output->triangles[idTri][1]][0] << " " <<
                //     output->points[output->triangles[idTri][1]][1] << ENDLINE; ERROR <<
                //     output->points[output->triangles[idTri][2]][0] << " " <<
                //     output->points[output->triangles[idTri][2]][1] << ENDLINE;
                //
                //     ENDFUN;
                //     continue;
                // }

                DelaunayKernel (p, output);

                count_inserted++;
                myboolean = true;
            }
        }

        INFOS << "Insert masscenters " << count_inserted << " [in loop " << count_loop << "]" << ENDLINE;
    }

    PurgeInvalids (output);
    INFOS << "Purge invalids ! " << ENDLINE;

    STATUS << "Done !" << ENDLINE;

    ENDFUN;
}
