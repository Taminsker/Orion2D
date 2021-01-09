#include "voronoi.hpp"

#include <algorithm>

using obj_t = std::vector<idx_t>;
using map_t = std::vector<obj_t>;

// real_t
// EquilibrateKernel (Mesh *mesh, ul_t toexclude, map_t &table)
//{
//    ul_t   numCell = mesh->points.size ();
//    real_t out     = 0.0;
//    Point  barycenter;

//    for (ul_t idCell = toexclude; idCell < numCell; ++idCell)
//    {
//        Point &centroid = mesh->points [idCell];

//        barycenter [0] = 0.0;
//        barycenter [1] = 0.0;

//        std::vector<idx_t> connectivity = table [idCell];
//        ul_t               counter      = connectivity.size ();

//        for (idx_t id : connectivity)
//        {
//            barycenter [0] += mesh->masscenters [USIGNED (id)][0];
//            barycenter [1] += mesh->masscenters [USIGNED (id)][1];
//        }

//        barycenter [0] /= static_cast<real_t> (counter);
//        barycenter [1] /= static_cast<real_t> (counter);

//        out += Norm (centroid - barycenter);

//        centroid [0] = barycenter [0];
//        centroid [1] = barycenter [1];
//    }

//    ul_t numTriangle = mesh->triangles.size ();
//    for (ul_t id = 0; id < numTriangle; ++id)
//        mesh->UpdateTriangle (id);

//    return out;
//}

// void
// EquilibrateByVoronoi (Mesh *mesh, ul_t toexclude)
//{
//    // PURGE INVALIDS
//    PurgeInvalids (mesh);

//    ul_t  numPoints = mesh->points.size ();
//    map_t table;
//    table.resize (numPoints);

//    for (Edge &e : mesh->edges)
//    {
//        if (e [2] != -1)
//        {
//            if (e [0] != -1)
//                table [USIGNED (e [0])].push_back (e [2]);

//            if (e [1] != -1)
//                table [USIGNED (e [1])].push_back (e [2]);
//        }

//        if (e [3] != -1)
//        {
//            if (e [0] != -1)
//                table [USIGNED (e [0])].push_back (e [3]);

//            if (e [1] != -1)
//                table [USIGNED (e [1])].push_back (e [3]);
//        }
//    }

//    for (auto &obj : table)
//    {
//        std::sort (obj.begin (), obj.end ());
//        obj.erase (std::unique (obj.begin (), obj.end ()), obj.end ());
//    }

//    real_t value = 1e20;
//    ul_t   it    = 0;
//    while (value > 1e-6 && it < 5000)
//    {
//        value = EquilibrateKernel (mesh, toexclude, table);
//        it++;
//    }
//    INFOS << "Iterate : " << it << " value " << value << ENDLINE;

//    return;
//}

real_t
EquilibrateKernel (Mesh *mesh, ul_t toexclude, map_t &table)
{
    ul_t   numCell = mesh->points.size ();
    real_t out     = 0.0;
    Point  newcentroid;

    for (ul_t idCell = toexclude; idCell < numCell; ++idCell)
    {
        Point &centroid = mesh->points [idCell];

        newcentroid [0] = 0.0;
        newcentroid [1] = 0.0;

        std::vector<idx_t> connectivity = table [idCell];
        ul_t               counter      = connectivity.size ();
        real_t             totalArea    = 0.0;

        for (ul_t id = 0; id < counter - 1; ++id)
        {
            Point &s1 = mesh->masscenters [USIGNED (connectivity [id])];
            Point &s2 = mesh->masscenters [USIGNED (connectivity [id + 1])];

            real_t area = ComputeArea (centroid, s1, s2);
            totalArea += area;

            newcentroid [0] += area * (centroid [0] + s1 [0] + s2 [0]) / 3.;
            newcentroid [1] += area * (centroid [1] + s1 [1] + s2 [1]) / 3.;
        }
        {
            Point &s1 = mesh->masscenters [USIGNED (connectivity [0])];
            Point &s2 = mesh->masscenters [USIGNED (connectivity [counter - 1])];

            real_t area = ComputeArea (centroid, s1, s2);
            totalArea += area;

            newcentroid [0] += area * (centroid [0] + s1 [0] + s2 [0]) / 3.;
            newcentroid [1] += area * (centroid [1] + s1 [1] + s2 [1]) / 3.;
        }

        newcentroid [0] /= totalArea;
        newcentroid [1] /= totalArea;

        out += std::pow (Norm (centroid - newcentroid), 2);

        centroid [0] = newcentroid [0];
        centroid [1] = newcentroid [1];
    }

    ul_t numTriangle = mesh->triangles.size ();
    for (ul_t id = 0; id < numTriangle; ++id)
        mesh->UpdateTriangle (id);

    return out;
}

void
EquilibrateByVoronoi (Mesh *mesh, ul_t toexclude)
{
    BEGIN << "Equilibrate by Voronoi diagram" << ENDLINE;

    // PURGE INVALIDS
    PurgeInvalids (mesh);

    ul_t  numPoints = mesh->points.size ();
    map_t table;
    table.resize (numPoints);

    for (Edge &e : mesh->edges)
    {
        if (e [2] != -1)
        {
            if (e [0] != -1)
                table [USIGNED (e [0])].push_back (e [2]);

            if (e [1] != -1)
                table [USIGNED (e [1])].push_back (e [2]);
        }

        if (e [3] != -1)
        {
            if (e [0] != -1)
                table [USIGNED (e [0])].push_back (e [3]);

            if (e [1] != -1)
                table [USIGNED (e [1])].push_back (e [3]);
        }
    }

    for (ul_t idobj = toexclude; idobj < numPoints; ++idobj)
    {
        obj_t &obj = table [idobj];

        std::sort (obj.begin (), obj.end ());
        obj.erase (std::unique (obj.begin (), obj.end ()), obj.end ());

        ul_t objsize = obj.size ();

        for (ul_t id = 1; id < objsize; ++id)
        {
            Triangle &tri1 = mesh->triangles [USIGNED (obj [id])];
            Edge      edge;

            for (ul_t cursor = id + 1; cursor < objsize; ++cursor)
            {
                Triangle &tri2 = mesh->triangles [USIGNED (obj [cursor])];

                if (SharedEdge (tri1, tri2, &edge))
                {
                    idx_t temp   = obj [id];
                    obj [id]     = obj [cursor];
                    obj [cursor] = temp;

                    break;
                }
            }
        }
    }

    INFOS << "Build the connectivity table" << ENDLINE;

    real_t value = 1e20;
    real_t total = 0.;
    ul_t   it    = 0;
    while (value > 1e-12 && it < 5000)
    {
        value = EquilibrateKernel (mesh, toexclude, table);
        total += value;
        it++;
    }

    INFOS << "Iterate " << it << " times,  last displacement norm = " << value << " | total displacement = " << total
          << ENDLINE;

    ENDFUN;
    return;
}
