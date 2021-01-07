#ifndef SRC_CORE_EDGE_HPP
#define SRC_CORE_EDGE_HPP

#include <vector>

#include "../Tools/smartpointer.hpp"
#include "templates.h"

struct Point;
struct Cell;

struct Edge
{
    std::vector<Smart<Point>> points;  //! List of points
    std::vector<Smart<Cell>>  cells;   //! List of cells
};

#endif /* SRC_CORE_EDGE_HPP */
