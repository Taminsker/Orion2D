
#include "Algorithm/algorithm.hpp"
#include "Core/core.hpp"
#include "IO/io.hpp"

int
main (int argc, char ** argv)
{
    if (argc < 2)
    {
        ERROR << "Use : " << argv [0] << " filename.mesh" << ENDLINE;
        return EXIT_FAILURE;
    }

    // INPUT
    std::string filename = argv [1];

    Mesh input;
    Read (&input, filename);

    // // // TRIANGULATION
    // Mesh mesh;
    // VOID_USE (mesh);
    //
    // // Force  Boundaries
    // ForceBoundaries (&input, &mesh);
    //
    // // OUTPUT
    // Write (&mesh, filename + ".orion.mesh");

    return EXIT_SUCCESS;
}
