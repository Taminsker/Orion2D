#ifndef SRC_DATA_MESH_HPP
#define SRC_DATA_MESH_HPP

#include <iostream>
#include <vector>

#include "../orionheader.hpp"
#include "cell.hpp"
#include "edge.hpp"
#include "macros.hpp"
#include "point.hpp"

class Mesh
{
public:
    Mesh ();
    ~Mesh ();

    GET_THE (Point, m_points)
    GET_NUMBER_OF (Point, m_points)
    INSERT_THE (Point, m_points)
    REMOVE_THE (Point, m_points)
    RESERVE_NUM_OF (Point, m_points)

    GET_THE (Cell, m_cells)
    GET_NUMBER_OF (Cell, m_cells)
    INSERT_THE (Cell, m_cells)
    REMOVE_THE (Cell, m_cells)
    RESERVE_NUM_OF (Cell, m_cells)

    GET_THE (Edge, m_edges)
    GET_NUMBER_OF (Edge, m_edges)
    INSERT_THE (Edge, m_edges)
    REMOVE_THE (Edge, m_edges)
    RESERVE_NUM_OF (Edge, m_edges)

    void Print ();

protected:
    std::vector<Point *> m_points;
    std::vector<Cell *>  m_cells;
    std::vector<Edge *>  m_edges;

private:
    Mesh (const Mesh &) = delete;
};

#endif /* SRC_DATA_MESH_HPP */
