#include "edge.hpp"

#include "cell.hpp"
#include "point.hpp"

Edge::Edge () : m_points ({}),
                m_cells ({})
{
}

Edge::~Edge ()
{
    m_points.clear ();
    m_cells.clear ();
}