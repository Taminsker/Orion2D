#include "cell.hpp"

#include "edge.hpp"
#include "point.hpp"

Cell::Cell () : m_points ({}),
                m_neighs ({}),
                m_edges ({})
{
}

Cell::~Cell ()
{
    m_points.clear ();
    m_neighs.clear ();
    m_edges.clear ();
}
