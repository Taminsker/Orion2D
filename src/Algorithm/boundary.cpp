#include "boundary.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

#include "../Core/core.hpp"
#include "../orionglobal.hpp"

void
ForceBoundaries (Mesh *input, Mesh *output)
{
    BEGIN << "Force boundaries" << ENDLINE;

    INFOS << "Number of targets edges : " << input->edgesbypoints.size () << ENDLINE;

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

    auto hashFun = [numPoints] (idx_t i, idx_t j) -> key_t {
        return static_cast<key_t> (i) + static_cast<key_t> (numPoints) * static_cast<key_t> (j);
    };

    map_t theMap;

    idx_t index = 0;
    for (Edge &e : output->edgesbypoints)
        theMap.insert ({hashFun (e [0], e [1]), {index++}});

    ////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// Retrieve
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////

    ul_t countSwap = 0;
    for (Edge &e : input->edgesbypoints)
    {
        e [0] += 4;
        e [1] += 4;

        if (theMap.find (hashFun (e [0], e [1])) != theMap.end ())
            continue;

        std::vector<ul_t> listE0, listE1;
        Edge              edge;
        bool              found = false;

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
                for (ul_t id : listE0)
                    if (SharedEdge (output->triangles [id], tri))
                    {
                        edge [0] = static_cast<idx_t> (id);
                        edge [1] = static_cast<idx_t> (idTri);

                        found = true;
                        break;
                    }

                if (found)
                    break;

                listE0.push_back (idTri);
            }

            ////////////////////////////////////////////////////////////////////////////////////////////
            //
            // List triangles which have the point e[0]
            //
            ////////////////////////////////////////////////////////////////////////////////////////////

            if (PointOnTriangle (tri, e [1]))
            {
                for (ul_t id : listE1)
                    if (SharedEdge (output->triangles [id], tri))
                    {
                        edge [0] = static_cast<idx_t> (id);
                        edge [1] = static_cast<idx_t> (idTri);

                        found = true;
                        break;
                    }

                if (found)
                    break;

                listE1.push_back (idTri);
            }
        }

        countSwap++;
    }

    INFOS << "Number of edge swap : " << countSwap << ENDLINE;
    STATUS << "Done !" << ENDLINE;

    ENDFUN;
    return;
}
