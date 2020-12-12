#include "io.hpp"

#include "../Core/core.hpp"

void
Read (Mesh * mesh, std::string filename)
{
    // VOID_USE (mesh); (void)mesh;
    // VOID_USE (filename);

    std::ifstream fichier (filename);

    // Vérification que l'ouverture a fonctionné
    if (! fichier)
    {
        std::cout << "ERREUR : lecture du fichier " << filename << " impossible." << std::endl;
        return;
    }

    std::string mot = "";

    // Lecture du fichier tant qu'on n'est pas arrivé à la fin
    while (! fichier.eof ())
    {
        // On lit un mot
        fichier >> mot >> std::ws; // ws = pour ne pas lire les espaces

        if (mot == "Vertices")
        {
            int nbPoints = 0;
            fichier >> nbPoints >> std::ws;

            for (int k = 0; k < nbPoints; ++k)
            {
                Point* newPoint = new Point ();
                fichier >> newPoint->x >> newPoint->y >> newPoint->z >> std::ws;

                mesh->Insert (newPoint);
            }

            std::cout << "\nNombre de sommets : " << nbPoints << "." << std::endl;
            std::cout << "\nNombre de sommets : " << mesh->GetNumberOfPoints ()  << "." << std::endl;
        }

        else if (mot == "Edges")
        {
            int nbEdges = 0;
            fichier >> nbEdges >> std::ws;

            for (int k = 0; k < nbEdges; ++k)
            {
                int index_pt1, index_pt2, couleur;
                Edge* newEdge = new Edge ();
                fichier >> index_pt1 >> index_pt2 >> couleur >> std::ws;

                // Rajout des 2 points qui définissent l'arête newEdge
                newEdge->Insert (mesh->GetPoint (index_pt1 - 1));
                newEdge->Insert (mesh->GetPoint (index_pt2 - 1));

                // Signaler que les 2 points appartiennent à l'arête newEdge
                mesh->GetPoint (index_pt1-1)->InsertNeighEdge (newEdge);
                mesh->GetPoint (index_pt2-1)->InsertNeighEdge (newEdge);

                mesh->Insert (newEdge);

            }

            std::cout << "\nNombre d'arêtes : " << nbEdges << "." << std::endl;
            std::cout << "\nNombre d'arêtes : " <<  mesh->GetNumberOfEdges () << "." << std::endl;
        }

        else if (mot == "Triangles")
        {
            int nbTriangles = 0;
            fichier >> nbTriangles >> std::ws;

            for (int k = 0; k < nbTriangles; ++k)
            {
                int index_pt1, index_pt2, index_pt3, couleur;
                Cell* newCell = new Cell ();
                fichier >> index_pt1 >> index_pt2 >> index_pt3 >> couleur >> std::ws;

                // Rajout des 3 points qui définissent la cellule newCell
                newCell->Insert (mesh->GetPoint (index_pt1 - 1));
                newCell->Insert (mesh->GetPoint (index_pt2 - 1));
                newCell->Insert (mesh->GetPoint (index_pt3 - 1));

                // Signaler que les 3 points appartiennent à la cellule newCell
                mesh->GetPoint (index_pt1-1)->InsertNeighCell (newCell);
                mesh->GetPoint (index_pt2-1)->InsertNeighCell (newCell);
                mesh->GetPoint (index_pt3-1)->InsertNeighCell (newCell);

                mesh->Insert (newCell);
            }

            std::cout << "\nNombre de triangles : " <<  nbTriangles << "." << std::endl;
            std::cout << "\nNombre de triangles : " <<  mesh->GetNumberOfCells () << "." << std::endl;
        }
    }

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
