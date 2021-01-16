#include "delaunay.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>

// Pour savoir si le point p est dans le cercle circonscrit à la cellule edge
bool
PointInCircTri (Mesh *mesh, Point &p, ul_t id)
{
    if (!IsValid (mesh->triangles [id]))
        return false;

    Point & center = mesh->circumcenters [id];
    real_t &radius = mesh->radius [id];

    if (Norm (p - center) < radius - 1E-10)
        return true;

    return false;
}

bool
PointInTriangle (Mesh *mesh, Point &p, ul_t id)
{
    if (!IsValid (mesh->triangles [id]))
        return false;

    Triangle &tri = mesh->triangles [id];

    Point &pA = mesh->points [static_cast<ul_t> (tri [0])];
    Point &pB = mesh->points [static_cast<ul_t> (tri [1])];
    Point &pC = mesh->points [static_cast<ul_t> (tri [2])];

    Point u_AB = pB - pA;
    Point u_AP = p - pA;
    Point u_AC = pC - pA;

    double z_ABAP = u_AB [0] * u_AP [1] - u_AB [1] * u_AP [0];
    double z_ABAC = u_AB [0] * u_AC [1] - u_AB [1] * u_AC [0];

    if (z_ABAP * z_ABAC < 0)
        return false;

    Point u_BC = pC - pB;
    Point u_BP = p - pB;

    double z_BCBP = u_BC [0] * u_BP [1] - u_BC [1] * u_BP [0];
    double z_BCBA = -(u_BC [0] * u_AB [1] - u_BC [1] * u_AB [0]);

    if (z_BCBP * z_BCBA < 0)
        return false;

    Point u_CP = p - pC;

    double z_CACP = -(u_AC [0] * u_CP [1] - u_AC [1] * u_CP [0]);
    double z_CACB = u_AC [0] * u_BC [1] - u_AC [1] * u_BC [0];

    if (z_CACP * z_CACB < 0)
        return false;

    return true;
}

ul_t
DelaunayKernel (Point &p, Mesh *output)
{
    ul_t numInvalids = 0;

    output->InsertPoint (p);

    ul_t numTriangles = output->triangles.size ();
    int  idInserted   = static_cast<int> (output->points.size ()) - 1;

    std::vector<Edge> edges;

    for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
        if (PointInCircTri (output, p, idTri))
        {
            Triangle &tri = output->triangles [idTri];
            edges.insert (std::end (edges),
                          {{tri [0], tri [1], -1, -1}, {tri [1], tri [2], -1, -1}, {tri [0], tri [2], -1, -1}});

            InvalidThis (tri);
            numInvalids++;
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

    return numInvalids;
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

    ul_t counter      = 0;
    ul_t numPoints    = mesh->points.size ();
    ul_t numTriangles = mesh->triangles.size ();

    for (ul_t idPoint = 0; idPoint < numPoints; ++idPoint)
        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
            if (!PointBelongsTriangle (mesh->triangles [idTri], static_cast<idx_t> (idPoint)))
                if (PointInCircTri (mesh, mesh->points [idPoint], idTri))
                    counter++;

    if (counter == 0)
        INFOS << "Everything is good ! " << ENDLINE;
    else
        ERROR << counter << " points don't satisfy the criterion.." << ENDLINE;

    STATUS << "Done !" << ENDLINE;
    ENDFUN;

    return;
}

void
InsertMasscenter (Mesh *input, Mesh *output, ul_t maxiter)
{
    BEGIN << "Insert masscenters [max = " << maxiter << " loops]" << ENDLINE;

    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //    //
    //    // Insert masscenters
    //    //
    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ul_t numEdge     = input->edges.size ();
    ul_t numInvalids = 0;

    struct obj_t
    {
        Point  pt              = {0, 0};
        real_t size_prescribed = 0.;
    };

    std::vector<obj_t> list (numEdge);

    real_t sumprescribed = 0;
    for (ul_t id = 0; id < numEdge; ++id)
    {
        Point &p1 = input->points [USIGNED (input->edges [id][0])];
        Point &p2 = input->points [USIGNED (input->edges [id][1])];

        list [id].pt [0] = (p1 [0] + p2 [0]) / 2.;
        list [id].pt [1] = (p1 [1] + p2 [1]) / 2.;

        real_t value              = Norm (p1 - p2);
        list [id].size_prescribed = value;
        sumprescribed += value;
    }

    bool myboolean      = true;
    ul_t count_loop     = 0;
    ul_t count_inserted = 0;

    std::cout << std::setw (6) << "loop #" << SPC "add #" << SPC "total #" << SPC "stack #" << SPC "tri #" << ENDLINE;

    while (myboolean && count_loop < maxiter)
    {
        myboolean = false;
        count_loop++;

        ul_t current_count = 0;
        ul_t numTriangles  = output->triangles.size ();
        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
        {
            if (!IsValid (output->triangles [idTri]))
                continue;

            /////////////////////////////////////////////////////////////////////////////////////////////
            Point &masscenter = output->masscenters [idTri];
            //            Point & circumcenter = output->circumcenters [idTri];
            const real_t &area     = output->areas [idTri];
            const real_t &inradius = output->inradius [idTri];
            //            const real_t &maxlength = output->maxlength [idTri];
            /////////////////////////////////////////////////////////////////////////////////////////////

            real_t coeff     = 0.;
            real_t sumweight = 0.;
            for (obj_t obj : list)
            {
                real_t dist = std::pow (Norm (masscenter - obj.pt), 2);
                sumweight += 1. / dist;
                coeff += obj.size_prescribed / dist;
            }

            coeff /= sumweight;

            // 1.5 && 0.26 && inradius > 0.6 * coeff
            if (area > (coeff * coeff / 2.0) && inradius > 0.25 * coeff)
            {
                numInvalids += DelaunayKernel (masscenter, output);

                current_count++;
                myboolean = true;
            }
        }

        count_inserted += current_count;

        //        INFOS << "Loop : " << count_loop << " [" << current_count << "] " << count_inserted << " inserted |
        //        stack "
        //              << numInvalids << " | tri " << numTriangles << "    \r" << FLUSHLINE;

        std::cout << std::setw (6) << count_loop << SPC current_count << SPC count_inserted << SPC numInvalids
                  << SPC numTriangles << ENDLINE;

        if (numInvalids > 30000)
        {
            PurgeInvalids (output);
            numInvalids = 0;
        }
    }

    ENDFUN;

    PurgeInvalids (output);
    INFOS << "Purge invalids ! " << ENDLINE;

    BuildEdges (output);
    STATUS << "Done !" << ENDLINE;

    ENDFUN;
}

void
InsertMiddleEdges (Mesh *input, Mesh *output, ul_t maxiter)
{
    BEGIN << "Insert middle edges [max = " << maxiter << " loops]" << ENDLINE;

    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //    //
    //    // Insert middle of edges
    //    //
    //    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ul_t numEdge      = input->edges.size ();
    ul_t numToExclude = input->points.size ();
    ul_t numInvalids  = 0;

    struct obj_t
    {
        Point  pt              = {0, 0};
        real_t size_prescribed = 0.;
    };

    std::vector<obj_t> list (numEdge);

    real_t sumprescribed = 0;
    for (ul_t id = 0; id < numEdge; ++id)
    {
        Point &p1 = input->points [USIGNED (input->edges [id][0])];
        Point &p2 = input->points [USIGNED (input->edges [id][1])];

        list [id].pt [0] = (p1 [0] + p2 [0]) / 2.;
        list [id].pt [1] = (p1 [1] + p2 [1]) / 2.;

        real_t value              = Norm (p1 - p2);
        list [id].size_prescribed = value;
        sumprescribed += value;
    }

    bool myboolean      = true;
    ul_t count_loop     = 0;
    ul_t count_inserted = 0;

    std::cout << std::setw (6) << "loop #" << SPC "add #" << SPC "total #" << SPC "stack #" << SPC "tri #" << ENDLINE;

    while (myboolean && count_loop < maxiter)
    {
        myboolean = false;
        count_loop++;

        ul_t current_count = 0;
        ul_t numTriangles  = output->triangles.size ();
        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
        {
            if (!IsValid (output->triangles [idTri]))
                continue;

            Triangle &tri = output->triangles [idTri];
            for (std::array<ul_t, 2> idLoc : std::vector<std::array<ul_t, 2>> ({{0, 1}, {1, 2}, {0, 2}}))
            {
                if (tri [idLoc [0]] < int (numToExclude) && tri [idLoc [1]] < int (numToExclude) && count_loop != 1)
                    continue;

                if (!IsValid (output->triangles [idTri]))
                    continue;
                /////////////////////////////////////////////////////////////////////////////////////////////

                Point &p1 = output->points [USIGNED (tri [idLoc [0]])];
                Point &p2 = output->points [USIGNED (tri [idLoc [1]])];

                Point pointMiddle = 0.5 * (p1 + p2);

                real_t length = Norm (p1 - p2);
                /////////////////////////////////////////////////////////////////////////////////////////////

                real_t coeff     = 0.;
                real_t sumweight = 0.;
                for (obj_t obj : list)
                {
                    real_t dist = std::pow (Norm (pointMiddle - obj.pt), 2);
                    sumweight += 1. / dist;
                    coeff += obj.size_prescribed / dist;
                }

                coeff /= sumweight;

                //                ERROR << "length : " << length << " coeff " << coeff << ENDLINE;
                // 1.5 && 0.26 && inradius > 0.6 * coeff
                if (length > coeff)
                {
                    numInvalids += DelaunayKernel (pointMiddle, output);

                    current_count++;
                    myboolean = true;
                }
            }
        }

        count_inserted += current_count;

        //        INFOS << "Loop : " << count_loop << " [" << current_count << "] " << count_inserted << " inserted |
        //        stack "
        //              << numInvalids << " | tri " << numTriangles << "    \r" << FLUSHLINE;

        std::cout << std::setw (6) << count_loop << SPC current_count << SPC count_inserted << SPC numInvalids
                  << SPC numTriangles << ENDLINE;

        if (numInvalids > 30000)
        {
            PurgeInvalids (output);
            numInvalids = 0;
        }
    }

    ENDFUN;

    PurgeInvalids (output);
    INFOS << "Purge invalids ! " << ENDLINE;

    BuildEdges (output);
    STATUS << "Done !" << ENDLINE;

    ENDFUN;
}
