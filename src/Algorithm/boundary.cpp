#include "boundary.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>

#include "../Core/core.hpp"
#include "../orionglobal.hpp"

// The object in the hash map
using edgemap_t = std::set<ul_t>;

// IN THE HEADER
// using triobj_t = std::array<idx_t, 2>;
// using trimap_t = std::vector<std::vector<triobj_t>>;

void
ForceBoundaries (Mesh *input, Mesh *output)
{
    BEGIN << "Retrieve boundaries" << ENDLINE;

    INFOS << "Number of targets edges : " << input->edges.size () << ENDLINE;

    ////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Here we need to look at the edges in input and verify they are present in the output
    //
    ////////////////////////////////////////////////////////////////////////////////////////////

    ul_t numPoints    = output->points.size ();
    ul_t numTriangles = output->triangles.size ();

    auto hashEdgeMap = [numPoints] (idx_t i, idx_t j) -> ul_t { return USIGNED (i) + numPoints * USIGNED (j); };

    edgemap_t edgeMap, existsMap;

    //    idx_t index = 0;
    for (Edge &e : output->edges)
        edgeMap.insert (hashEdgeMap (e [0], e [1]));

    ////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// Retrieve Edges
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////

    ul_t countSwap = 0;
    //    index          = 0;

    for (Edge e : input->edges)
    {
        e [0] += 4;
        e [1] += 4;

        // ajout prématuré
        existsMap.insert (hashEdgeMap (std::min (e [0], e [1]), std::max (e [0], e [1])));

        if ((edgeMap.find (hashEdgeMap (e [0], e [1])) != edgeMap.end ()))
            continue;

        std::array<std::vector<ul_t>, 2> list;
        Edge                             edge = {-1, -1, -1, -1};

        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
        {
            Triangle &tri = output->triangles [idTri];

            for (ul_t idList = 0; idList < 2; ++idList)
                if (PointBelongsTriangle (tri, e [idList]))
                {
                    for (ul_t id : list [1 - idList])
                        if (SharedEdge (output->triangles [id], tri, &edge))
                        {
                            edge [2] = std::min (SIGNED (id), SIGNED (idTri));
                            edge [3] = SIGNED (id) + SIGNED (idTri) - edge [2];

                            goto outloops;
                        }

                    list [idList].push_back (idTri);
                }
        }

    outloops:

        /// Swap edges

        Triangle &tri1 = output->triangles [static_cast<ul_t> (edge [2])];
        Triangle &tri2 = output->triangles [static_cast<ul_t> (edge [3])];

        idx_t res [2];
        res [0] = tri1 [0] + tri1 [1] + tri1 [2] - edge [0] - edge [1];
        res [1] = tri2 [0] + tri2 [1] + tri2 [2] - edge [0] - edge [1];

        output->InsertTriangle (edge [0], res [0], res [1]);
        output->InsertTriangle (edge [1], res [1], res [0]);

        InvalidThis (tri1);
        InvalidThis (tri2);

        countSwap++;
    }

    if (countSwap == 0)
        WARNING << "No swaps needed !" << ENDLINE;
    else
        STATUS << "Count swaps  : " << countSwap << ENDLINE;

    BuildEdges (output);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// Delete exterior
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    numTriangles = output->triangles.size ();

    std::vector<idx_t> colored;
    trimap_t           triMap;

    triMap.resize (numTriangles, std::vector<triobj_t> ());
    colored.resize (numTriangles, 0);

    for (Edge &e : output->edges)
    {
        if (e [2] == -1 || !IsValid (output->triangles [USIGNED (e [2])]))

            continue;

        if (e [3] == -1 || !IsValid (output->triangles [USIGNED (e [3])]))
            continue;

        bool found = (existsMap.find (hashEdgeMap (e [0], e [1])) != existsMap.end ());
        found      = found || (existsMap.find (hashEdgeMap (e [1], e [0])) != existsMap.end ());

        triMap [USIGNED (e [2])].push_back ({e [3], 1 - 2 * SIGNED (found)});
        triMap [USIGNED (e [3])].push_back ({e [2], 1 - 2 * SIGNED (found)});
    }

    //        PurgeInvalids (output);
    BuildEdges (output);

    for (Edge &e : output->edges)
        if (e [0] == 0 || e [1] == 0)
        {
            ul_t idTri = USIGNED (std::max (e [2], e [3]));
            INFOS << "beg : " << idTri << ENDLINE;

            PropagateTheColor (&triMap, &colored, idTri, --colored [idTri]);

            break;
        }

    ul_t index = 0;
    for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
    {
        if (colored [idTri] == -1)
        {
            InvalidThis (output->triangles [idTri]);
            index++;
        }

        if (colored [idTri] == 0)
        {
            INFOS << "not colored  : " << idTri << ENDLINE;
        }
    }

    INFOS << "Count deleted  : " << index << ENDLINE;

    // Delete the box

    for (idx_t idPoint = 0; idPoint < 4; ++idPoint)
        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
            if (PointBelongsTriangle (output->triangles [idTri], idPoint))
                InvalidThis (output->triangles [idTri]);

    for (Triangle &tri : output->triangles)
    {
        tri [0] -= 4;
        tri [1] -= 4;
        tri [2] -= 4;
    }

    for (ul_t id = 4; id < numPoints; ++id)
        output->points [id - 4] = output->points [id];

    output->points.resize (numPoints - 4);

    PurgeInvalids (output);
    BuildEdges (output);

    ENDFUN;

    return;
}

void
PropagateTheColor (trimap_t *triMap, std::vector<idx_t> *colored, ul_t idTri, idx_t color)
{
    for (triobj_t &obj : (*triMap) [idTri])
        if ((*colored) [USIGNED (obj [0])] == 0)
        {
            idx_t cc = (*colored) [USIGNED (obj [0])] = color * obj [1];

            PropagateTheColor (triMap, colored, USIGNED (obj [0]), cc);
        }

    return;
}
