#ifndef SRC_DATA_MESH_HPP
#define SRC_DATA_MESH_HPP

#include <vector>

#include "../Tools/smartpointer.hpp"

struct Point;
struct Cell;
struct Edge;

struct Mesh
{
    Mesh () = default;
    ~Mesh ();

    std::vector<Smart<Cell>>  cells;   //! List of cells
    std::vector<Smart<Edge>>  edges;   //! List of edges
    std::vector<Smart<Point>> points;  //! List of points
};

void
PrintStatistics (Mesh *mesh, const char *name);

void
PurgeInvalid (Mesh *mesh);

void
ClearAllMembers (Mesh *mesh);

#endif /* SRC_DATA_MESH_HPP */
