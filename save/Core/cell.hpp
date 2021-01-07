#ifndef SRC_DATA_CELL_HPP
#define SRC_DATA_CELL_HPP

#include <vector>

#include "../Tools/smartpointer.hpp"
#include "templates.h"

struct Point;
struct Edge;

struct Cell
{
    std::vector<Smart<Point>> points;  //! List of points
    std::vector<Smart<Cell>>  neighs;  //! List of cells
    std::vector<Smart<Edge>>  edges;   //! List of edges
};

#endif /* SRC_DATA_CELL_HPP */
