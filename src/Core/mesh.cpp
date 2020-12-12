#include "mesh.hpp"

#include "cell.hpp"
#include "edge.hpp"
#include "point.hpp"

Mesh::Mesh () : m_points ({}),
                m_cells ({}),
                m_edges ({})
{
}

Mesh::~Mesh ()
{
    for (Point * p : m_points)
        delete p;
    m_points.clear ();

    for (Cell * c : m_cells)
        delete c;
    m_cells.clear ();

    for (Edge * e : m_edges)
        delete e;
    m_edges.clear ();
}

void
Mesh::Print ()
{
    BEGIN << "Mesh stats" << ENDLINE;
    std::cout << TREE_BRANCH << " Number of points : " << m_points.size () << ENDLINE;
    std::cout << TREE_BRANCH << " Number of edges  : " << m_edges.size () << ENDLINE;
    std::cout << TREE_BRANCH << " Number of cells  : " << m_cells.size () << ENDLINE;

    ENDFUN;
    return;
}
