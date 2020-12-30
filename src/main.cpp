
#include "Algorithm/algorithm.hpp"
#include "Core/core.hpp"
#include "IO/io.hpp"

error_t
main (int argc, char ** argv)
{
    if (argc < 2)
    {
        ERROR << "Use : " << argv [0] << " filename.mesh" << ENDLINE;
        return EXIT_FAILURE;
    }

    std::cout << COLOR_YELLOW << std::string (60, '-') << ENDLINE;
    std::cout << COLOR_YELLOW << REVERSE << "Welcome in Orion2D !" << ENDLINE;
    std::cout << COLOR_YELLOW << std::string (60, '-') << ENDLINE;

    // INPUT
    std::string filename = argv [1];

    Mesh input;
    Read (&input, filename);
    input.Print ();

    ul_t numCells = input.GetNumberOfCells ();
    std::vector<real_t> qualities (numCells, -1.0);

    ComputeQualities (&input);

    histogram (qualities);


    // // // TRIANGULATION
    // Mesh mesh;
    // VOID_USE (mesh);
    //
    // // Force  Boundaries
    // ForceBoundaries (&input, &mesh);
    //
    // // OUTPUT
    // Write (&input, filename + ".orion.mesh");

    return EXIT_SUCCESS;
}
