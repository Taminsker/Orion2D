#include "boundary.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

#include "../Core/core.hpp"
#include "../orionglobal.hpp"
#include "swap.hpp"

void
ForceBoundaries (Mesh *input, Mesh *output)
{
    BEGIN << "Force boundaries" << ENDLINE;

    INFOS << "Number of targets edges : " << input->edges.size () << ENDLINE;

    ////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Here we need to look at the edges in input and verify they are present in the output
    //
    ////////////////////////////////////////////////////////////////////////////////////////////

    // The object in the hash map
    using hash_t = idx_t;
    using key_t  = ul_t;
    using map_t  = std::map<key_t, hash_t>;

    ul_t numPoints    = output->points.size ();
    ul_t numTriangles = output->triangles.size ();

    auto hashFun = [numPoints] (idx_t i, idx_t j) -> key_t { return USIGNED (i) + numPoints * USIGNED (j); };

    map_t theMap;

    idx_t index = 0;
    for (Edge &e : output->edges)
        theMap.insert ({hashFun (e [0], e [1]), {index++}});

    ////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// Retrieve
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////

    bool enable = false;
    if (std::abs (output->points [0][1] - output->points [1][1]) > 1e-6)
        enable = true;

    ul_t countSwap = 0;
    for (Edge e : input->edges)
    {
        if (enable)
        {
            e [0] += 4;
            e [1] += 4;
        }

        if (theMap.find (hashFun (e [0], e [1])) != theMap.end ())
            continue;

        std::vector<ul_t> listE0, listE1;
        bool              found = false;
        Edge              edge  = {-1, -1, -1, -1};

        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
        {
            Triangle &tri = output->triangles [idTri];

            ////////////////////////////////////////////////////////////////////////////////////////////
            //
            // List triangles which have the point e[0]
            //
            ////////////////////////////////////////////////////////////////////////////////////////////

            if (PointOnTriangle (tri, e [0]))
            {
                for (ul_t id : listE1)
                    if (SharedEdge (output->triangles [id], tri, &edge))
                    {
                        edge [2] = std::min (SIGNED (id), SIGNED (idTri));
                        edge [3] = SIGNED (id) + SIGNED (idTri) - edge [2];

                        found = true;
                        break;
                    }

                if (found)
                    break;

                listE0.push_back (idTri);
            }

            ////////////////////////////////////////////////////////////////////////////////////////////
            //
            // List triangles which have the point e[1]
            //
            ////////////////////////////////////////////////////////////////////////////////////////////

            if (PointOnTriangle (tri, e [1]))
            {
                for (ul_t id : listE0)
                    if (SharedEdge (output->triangles [id], tri, &edge))
                    {
                        edge [2] = std::min (SIGNED (id), SIGNED (idTri));
                        edge [3] = SIGNED (id) + SIGNED (idTri) - edge [2];

                        found = true;
                        break;
                    }

                if (found)
                    break;

                listE1.push_back (idTri);
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        //
        // Swap
        //
        ////////////////////////////////////////////////////////////////////////////////////////////
        Triangle &tri1 = output->triangles [static_cast<ul_t> (edge [2])];
        Triangle &tri2 = output->triangles [static_cast<ul_t> (edge [3])];

        ERROR << found << " " << edge [0] << " " << edge [1] << " " << edge [2] << " " << edge [3] << " " << ENDLINE;

        output->InsertTriangle (edge [0], edge [1], tri1 [0] + tri1 [1] + tri1 [2] - edge [0] - edge [1]);
        output->InsertTriangle (edge [0], edge [1], tri2 [0] + tri2 [1] + tri2 [2] - edge [0] - edge [1]);

        InvalidThis (tri1);
        InvalidThis (tri2);

        countSwap++;
    }

    if (countSwap == 0)
        WARNING << "No swaps needed !" << ENDLINE;
    else
        STATUS << "Count swaps  : " << countSwap << ENDLINE;

    STATUS << "Done !" << ENDLINE;
    ENDFUN;

    PurgeInvalids (output);
    BuildEdges (output);

    return;
}
