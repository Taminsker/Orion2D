#include "io.hpp"

#include "../Core/core.hpp"

void
Read (Mesh *mesh, std::string filename)
{
    // ORION_UNUSED (mesh); (void)mesh;
    // ORION_UNUSED (filename);

    std::ifstream fichier (filename);

    // Vérification que l'ouverture a fonctionné
    if (!fichier)
    {
        ERROR << "lecture du fichier " << filename << " impossible." << ENDLINE;
        return;
    }

    BEGIN << "Read the file " << filename << ENDLINE;

    std::string mot = "";

    // Lecture du fichier tant qu'on n'est pas arrivé à la fin
    while (!fichier.eof ())
    {
        // On lit un mot
        fichier >> mot >> std::ws;  // ws = pour ne pas lire les espaces

        if (mot == "Vertices")
        {
            ul_t nbPoints = 0;
            fichier >> nbPoints >> std::ws;

            mesh->points.reserve (nbPoints);

            Point  newPoint;
            int    couleur;
            real_t trash;

            for (ul_t k = 0; k < nbPoints; ++k)
            {
                fichier >> newPoint [0] >> newPoint [1] >> trash >> couleur >> std::ws;

                mesh->InsertPoint (newPoint);
            }

            INFOS << "Read points [" << nbPoints << "]." << ENDLINE;

            // INFOS << "Nombre de sommets : " << nbPoints << "." << ENDLINE;
            // INFOS << "Nombre de sommets : " << mesh->GetNumberOfPoints () << "." << ENDLINE;
        }
        else if (mot == "Edges")
        {
            ul_t nbEdges = 0;
            fichier >> nbEdges >> std::ws;

            mesh->edgesbypoints.reserve (nbEdges);

            idx_t index_pt1, index_pt2;
            int   couleur;

            for (ul_t k = 0; k < nbEdges; ++k)
            {
                fichier >> index_pt1 >> index_pt2 >> couleur >> std::ws;

                mesh->InsertEdgeByPoint (--index_pt1, --index_pt2);
            }

            INFOS << "Read edges [" << nbEdges << "]." << ENDLINE;

            // INFOS << "Nombre d'arêtes : " << nbEdges << "." << ENDLINE;
            // INFOS << "Nombre d'arêtes : " << mesh->GetNumberOfEdges () << "." << ENDLINE;
        }
        else if (mot == "Triangles")
        {
            ul_t nbTriangles = 0;

            fichier >> nbTriangles >> std::ws;

            mesh->triangles.reserve (nbTriangles);
            mesh->areas.reserve (nbTriangles);
            mesh->circumcenters.reserve (nbTriangles);
            mesh->masscenters.reserve (nbTriangles);
            mesh->radius.reserve (nbTriangles);
            mesh->qualities.reserve (nbTriangles);

            int index_pt1, index_pt2, index_pt3;
            int couleur;

            for (ul_t k = 0; k < nbTriangles; ++k)
            {
                fichier >> index_pt1 >> index_pt2 >> index_pt3 >> couleur >> std::ws;

                mesh->InsertTriangle (--index_pt1, --index_pt2, --index_pt3);
            }

            INFOS << "Read triangles [" << nbTriangles << "]." << ENDLINE;

            // INFOS << "Nombre de triangles : " << nbTriangles << "." << ENDLINE;
            // INFOS << "Nombre de triangles : " << mesh->GetNumberOfCells () << "." << ENDLINE;
        }
    }

    STATUS << "Done !" << ENDLINE;
    ENDFUN;
    return;
}

void
Write (Mesh *mesh, std::string filename)
{
    BEGIN << "Write the file " << filename << ENDLINE;

    std::ofstream out (filename);

    out << "MeshVersionFormatted\n2\nDimension\n2\n\nVertices" << std::endl;

    out << mesh->points.size () << std::endl;
    for (Point &p : mesh->points)
        out << SPC p [0] << SPC p [1] << SPC 1 << std::endl;

    INFOS << "Points written [" << mesh->points.size () << "]." << ENDLINE;

    out << "\nEdges" << std::endl;
    out << mesh->edgesbypoints.size () << std::endl;

    for (Edge &e : mesh->edgesbypoints)
        out << SPC e [0] + 1 << SPC e [1] + 1 << SPC 1 << std::endl;

    INFOS << "Edges written [" << mesh->edgesbypoints.size () << "]." << ENDLINE;

    out << "\n\nTriangles" << std::endl;
    out << mesh->triangles.size () << std::endl;

    for (Triangle &tri : mesh->triangles)
        out << SPC tri [0] + 1 << SPC tri [1] + 1 << SPC tri [2] + 1 << SPC 1 << std::endl;

    INFOS << "Cells written [" << mesh->triangles.size () << "]." << ENDLINE;

    out << "END" << std::endl;

    out.close ();

    STATUS << "Done !" << ENDLINE;

    ENDFUN;
    return;
}


void
WriteBB (Mesh *mesh, std::string filename)
{
    BEGIN << "Write[BB] the file " << filename << ENDLINE;

    std::ofstream out (filename);

    ul_t numTriangles = mesh->triangles.size ();
    out << "2 1 " << numTriangles << " 1 "<< std::endl;

    for (ul_t idTri = 0; idTri < numTriangles; ++idTri)
        out << SPC mesh->qualities [idTri] << std::endl;

    INFOS << "Qualities written [" << mesh->triangles.size () << "]." << ENDLINE;

    out.close ();

    STATUS << "Done !" << ENDLINE;

    ENDFUN;
    return;
}
