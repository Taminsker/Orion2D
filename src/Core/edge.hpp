#ifndef SRC_CORE_EDGE_HPP
#define SRC_CORE_EDGE_HPP

#include <vector>

#include "../orionheader.hpp"
#include "macros.hpp"

class Point;
class Cell;

class Edge
{
public:
    Edge ();
    ~Edge ();

    GET_THE (Point, m_points)
    GET_NUMBER_OF (Point, m_points)
    INSERT_THE (Point, m_points)
    REMOVE_THE (Point, m_points)

    GET_THE (Cell, m_cells)
    GET_NUMBER_OF (Cell, m_cells)
    INSERT_THE (Cell, m_cells)
    REMOVE_THE (Cell, m_cells)

protected:
    std::vector<Point *> m_points;
    std::vector<Cell *>  m_cells;

private:
    Edge (const Edge &) = delete;
};

#endif /* SRC_CORE_EDGE_HPP */
