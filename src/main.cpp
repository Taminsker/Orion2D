
#include <chrono>

#include "Algorithm/algorithm.hpp"
#include "Core/core.hpp"
#include "IO/io.hpp"
#include "orionglobal.hpp"

static std::string filename    = "";
static error_t     error       = EXIT_SUCCESS;
static bool        use_voronoi = false;
static bool        use_mass    = false;
static bool        use_check   = false;
static bool        use_force   = false;

static char message [] =
    "[OPTIONS]       -v, --voronoi    : equilibrate diagram of Voronoï\n"
    "                -m, --mass       : insert masscenters\n"
    "                -c, --check      : check delaunay criterion\n"
    "                -f, --force      : force boundaries and erase the box";

error_t
ParseArguments (int argc, char const **argv)
{
    if (argc < 2)
    {
        ERROR << "use " << argv [0] << " [OPTIONS] filename.mesh  " << ENDLINE;
        std::cerr << message << std::endl;

        return EXIT_FAILURE;
    }

    filename = std::string (argv [argc - 1]);

    for (ul_t id = 1; id < USIGNED (argc) - 1; ++id)
    {
        std::string temp = argv [id];

        if (temp == "-v" || temp == "--voronoi")
            use_voronoi = true;
        else if (temp == "-m" || temp == "--mass")
            use_mass = true;
        else if (temp == "-c" || temp == "--check")
            use_check = true;
        else if (temp == "-f" || temp == "--force")
            use_force = true;
        else
        {
            ERROR << "unknown parameter " << temp << ENDLINE;
            std::cerr << message << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

error_t
main (int argc, const char **argv)
{
    error = ParseArguments (argc, argv);
    USE_ERROR (error)

    std::cout << COLOR_YELLOW << std::string (50, '-') << ENDLINE;
    std::cout << COLOR_YELLOW << REVERSE << " Welcome in Orion2D !" << ENDLINE;
    std::cout << COLOR_YELLOW << std::string (50, '-') << ENDLINE;

    std::chrono::steady_clock::time_point begin_time = std::chrono::steady_clock::now ();

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // INPUT
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

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

    if (use_check)
        CheckDelaunayCriterion (&output);

    BuildEdges (&output);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Force  Boundaries
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    if (use_force)
    {
        ForceBoundaries (&input, &output);
        MakeHistogram (&output);
    }

    if (use_mass)
    {
        InsertMasscenter (&input, &output, 500);

        if (use_check)
            CheckDelaunayCriterion (&output);

        MakeHistogram (&output);
    }

    if (use_voronoi)
    {
        EquilibrateByVoronoiCentroids (&output, input.points.size ());

        if (use_check)
            CheckDelaunayCriterion (&output);

        MakeHistogram (&output);
    }

    PrintStatistics (&output, "output");

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

    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now ();

    std::cout << "**********************************************************" << std::endl;

    INFOS << "Time difference = "
          << std::chrono::duration_cast<std::chrono::milliseconds> (end_time - begin_time).count () << " [ms]"
          << ENDLINE;

    return EXIT_SUCCESS;
}
