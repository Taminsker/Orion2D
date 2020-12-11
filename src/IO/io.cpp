#include "io.hpp"

#include "../Core/core.hpp"

void
Read (Mesh * mesh, std::string filename)
{
    VOID_USE (mesh);
    VOID_USE (filename);

    return;
}

void
Write (Mesh * mesh, std::string filename)
{
    VOID_USE (mesh);
    VOID_USE (filename);

    // std::ofstream out (filename);

    // out << "MeshVersionFormatted\n 2\n Dimension\n 2\n\nVertices" << std::endl;

    // for (Point * p : mesh->points)
    //     out << SPC p->x << SPC p->y << SPC p->z << std::endl;

    // out << "\n\nTriangles" << std::endl;
    // out << mesh->cells.size () << std::endl;
    // for (Cell * c : mesh->cells)
    // {
    //     for (Point * p : c->points)
    //         out << SPC p->gid;
    //     out << SPC 0 << std::endl;
    // }

    // out << "END" << std::endl;

    // out.close ();

    return;
}