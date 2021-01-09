
#include "Algorithm/algorithm.hpp"
#include "Core/core.hpp"
#include "IO/io.hpp"
#include "orionglobal.hpp"

error_t
main (int argc, char **argv)
{
    if (argc < 2)
    {
        ERROR << "Use : " << argv [0] << " filename.mesh" << ENDLINE;
        return EXIT_FAILURE;
    }

    std::cout << COLOR_YELLOW << std::string (50, '-') << ENDLINE;
    std::cout << COLOR_YELLOW << REVERSE << " Welcome in Orion2D !" << ENDLINE;
    std::cout << COLOR_YELLOW << std::string (50, '-') << ENDLINE;

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // INPUT
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string filename = argv [1];

    Mesh input;
    Read (&input, filename);
    PrintStatistics (&input, "input");

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // TRIANGULATION
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    Mesh output;
    DelaunayTriangulation (&input, &output);
    EraseBox (&output);
    CheckDelaunayCriterion (&output);
    BuildEdges (&output);
    PrintStatistics (&output, "output");

    MakeHistogram (&output);

    InsertMasscenter (&input, &output, 30);
    BuildEdges (&output);
    PrintStatistics (&output, "output");
    MakeHistogram (&output);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Force  Boundaries
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    //    ForceBoundaries (&input, &output);
    //    EquilibrateByVoronoi (&output, input.points.size ());
    CheckDelaunayCriterion (&output);
    MakeHistogram (&output);

    //    ul_t numPoints    = output.points.size ();
    //    ul_t numTriangles = output.triangles.size ();

    //    for (idx_t idPoint = 0; idPoint < 4; ++idPoint)
    //        for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
    //            if (PointOnTriangle (output.triangles [idTri], idPoint))
    //                InvalidThis (output.triangles [idTri]);

    //    PurgeInvalids (&output);
    //    BuildEdges (&output);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // OUTPUT
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    size_t pos = filename.find (".mesh");
    if (pos != std::string::npos)
        filename.erase (pos, 5);

    Write (&output, filename + "_orion.mesh");
    WriteBB (&output, filename + "_orion.bb");

    return EXIT_SUCCESS;
}
