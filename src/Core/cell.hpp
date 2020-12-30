#ifndef SRC_DATA_CELL_HPP
#define SRC_DATA_CELL_HPP

#include <iostream>
#include <vector>

#include "../orionheader.hpp"
#include "macros.hpp"

class Point;
class Edge;

class Cell
{
public:
    Cell ();
    ~Cell ();

    GET_THE (Point, m_points)
    GET_NUMBER_OF (Point, m_points)
    INSERT_THE (Point, m_points)
    REMOVE_THE (Point, m_points)

    GET_THE (Cell, m_neighs)
    GET_NUMBER_OF (Cell, m_neighs)
    INSERT_THE (Cell, m_neighs)
    REMOVE_THE (Cell, m_neighs)

    GET_THE (Edge, m_edges)
    GET_NUMBER_OF (Edge, m_edges)
    INSERT_THE (Edge, m_edges)
    REMOVE_THE (Edge, m_edges)

protected:
    std::vector<Point *> m_points;
    std::vector<Cell *>  m_neighs;
    std::vector<Edge *>  m_edges;

private:
    Cell (const Cell &) = delete;
};

#endif /* SRC_DATA_CELL_HPP */
