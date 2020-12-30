#include "io.hpp"

#include "../Core/core.hpp"
#include "../Tools/progressbar.hpp"
#include "../orionheader.hpp"

void
Read (Mesh *mesh, std::string filename)
{
    // VOID_USE (mesh); (void)mesh;
    // VOID_USE (filename);

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

            mesh->ReserveNumberOfPoints (nbPoints);

            for (ul_t k = 0; k < nbPoints; ++k)
            {
                Point *newPoint = new Point ();
                int    couleur;

                fichier >> newPoint->x >> newPoint->y >> newPoint->z >> couleur >> std::ws;

                newPoint->SetGlobalIndex (static_cast<int> (k));

                mesh->Insert (newPoint, false);
            }

            INFOS << "Read points [" << nbPoints << "]." << ENDLINE;

            // INFOS << "Nombre de sommets : " << nbPoints << "." << ENDLINE;
            // INFOS << "Nombre de sommets : " << mesh->GetNumberOfPoints () << "." << ENDLINE;
        }

        else if (mot == "Edges")
        {
            ul_t nbEdges = 0;
            fichier >> nbEdges >> std::ws;

            mesh->ReserveNumberOfEdges (nbEdges);

            for (ul_t k = 0; k < nbEdges; ++k)
            {
                ul_t index_pt1, index_pt2;
                int  couleur;

                Edge *newEdge = new Edge ();

                fichier >> index_pt1 >> index_pt2 >> couleur >> std::ws;

                index_pt1--;
                index_pt2--;

                // Rajout des 2 points qui définissent l'arête newEdge
                newEdge->Insert (mesh->GetPoint (index_pt1));
                newEdge->Insert (mesh->GetPoint (index_pt2));

                // Signaler que les 2 points appartiennent à l'arête newEdge
                mesh->GetPoint (index_pt1)->InsertNeighEdge (newEdge);
                mesh->GetPoint (index_pt2)->InsertNeighEdge (newEdge);

                mesh->Insert (newEdge, false);
            }

            INFOS << "Read edges [" << nbEdges << "]." << ENDLINE;

            // INFOS << "Nombre d'arêtes : " << nbEdges << "." << ENDLINE;
            // INFOS << "Nombre d'arêtes : " << mesh->GetNumberOfEdges () << "." << ENDLINE;
        }

        else if (mot == "Triangles")
        {
            ul_t nbTriangles = 0;

            fichier >> nbTriangles >> std::ws;

            mesh->ReserveNumberOfCells (nbTriangles);

            for (ul_t k = 0; k < nbTriangles; ++k)
            {
                ul_t index_pt1, index_pt2, index_pt3;
                int  couleur;

                Cell *newCell = new Cell ();

                fichier >> index_pt1 >> index_pt2 >> index_pt3 >> couleur >> std::ws;

                index_pt1--;
                index_pt2--;
                index_pt3--;

                // Rajout des 3 points qui définissent la cellule newCell
                newCell->Insert (mesh->GetPoint (index_pt1));
                newCell->Insert (mesh->GetPoint (index_pt2));
                newCell->Insert (mesh->GetPoint (index_pt3));

                // Signaler que les 3 points appartiennent à la cellule newCell
                mesh->GetPoint (index_pt1)->InsertNeighCell (newCell);
                mesh->GetPoint (index_pt2)->InsertNeighCell (newCell);
                mesh->GetPoint (index_pt3)->InsertNeighCell (newCell);

                mesh->Insert (newCell, false);
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

    out << "MeshVersionFormatted\n2\nDimension\n3\n\nVertices" << std::endl;

    ul_t numPoints = mesh->GetNumberOfPoints ();

    out << numPoints << std::endl;
    for (ul_t idPoint = 0; idPoint < numPoints; ++idPoint)
    {
        Point *p = mesh->GetPoint (idPoint);

        out << SPC p->x << SPC p->y << SPC p->z << SPC 1 << std::endl;
    }

    INFOS << "Points written [" << mesh->GetNumberOfPoints () << "]." << ENDLINE;

    ul_t numEdges = mesh->GetNumberOfEdges ();

    out << "\nEdges" << std::endl;
    out << numEdges << std::endl;

    for (ul_t idEdge = 0; idEdge < numEdges; ++idEdge)
    {
        Edge *e = mesh->GetEdge (idEdge);

        ul_t numptOnEdge = e->GetNumberOfPoints ();

        for (ul_t idPoint = 0; idPoint < numptOnEdge; ++idPoint)
        {
            Point *p = e->GetPoint (idPoint);

            out << SPC p->GetGlobalIndex () + 1 << std::flush;
        }

        out << SPC 1 << std::endl;
    }

    INFOS << "Edges written [" << mesh->GetNumberOfEdges () << "]." << ENDLINE;

    ul_t numCells = mesh->GetNumberOfCells ();
    out << "\n\nTriangles" << std::endl;
    out << numCells << std::endl;

    for (ul_t idCell = 0; idCell < numCells; ++idCell)
    {
        Cell *c = mesh->GetCell (idCell);

        ul_t numptOnCell = c->GetNumberOfPoints ();

        for (ul_t idPoint = 0; idPoint < numptOnCell; ++idPoint)
        {
            Point *p = c->GetPoint (idPoint);

            out << SPC p->GetGlobalIndex () + 1 << std::flush;
        }

        out << SPC 1 << std::endl;
    }

    INFOS << "Cells written [" << mesh->GetNumberOfCells () << "]." << ENDLINE;

    out << "END" << std::endl;

    out.close ();

    STATUS << "Done !" << ENDLINE;

    ENDFUN;
    return;
}
