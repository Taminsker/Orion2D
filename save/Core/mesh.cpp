#include "mesh.hpp"

#include <iostream>

#include "../orionglobal.hpp"
#include "cell.hpp"
#include "edge.hpp"
#include "point.hpp"

Mesh::~Mesh () { ClearAllMembers (this); }

void
PrintStatistics (Mesh *mesh, const char *name)
{
    BEGIN << "Mesh stats " << name << ENDLINE;
    INFOS << " Number of points : " << CountNumberOfValids (mesh->points) << ENDLINE;
    INFOS << " Number of edges  : " << CountNumberOfValids (mesh->edges) << ENDLINE;
    INFOS << " Number of cells  : " << CountNumberOfValids (mesh->cells) << ENDLINE;

    ENDFUN;
    return;
}

void
PurgeInvalid (Mesh *mesh)
{
    std::for_each (std::begin (mesh->points), std::end (mesh->points), PurgeInvalid<Point>);
    std::for_each (std::begin (mesh->cells), std::end (mesh->cells), PurgeInvalid<Cell>);
    std::for_each (std::begin (mesh->edges), std::end (mesh->edges), PurgeInvalid<Edge>);

    PurgeInvalidInVector (mesh->points);
    PurgeInvalidInVector (mesh->cells);
    PurgeInvalidInVector (mesh->edges);
}

void
ClearAllMembers (Mesh *mesh)
{
    std::for_each (std::begin (mesh->points), std::end (mesh->points), ClearAllMembers<Point>);
    std::for_each (std::begin (mesh->cells), std::end (mesh->cells), ClearAllMembers<Cell>);
    std::for_each (std::begin (mesh->edges), std::end (mesh->edges), ClearAllMembers<Edge>);

    mesh->points.clear ();
    mesh->cells.clear ();
    mesh->edges.clear ();

    return;
}
