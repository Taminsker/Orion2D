#include "point.hpp"

// LES METHODES

// Constructeurs et destructeur

Point::Point (double xval, double yval) : x (xval),
                                          y (yval),
                                          m_listOfPoints ({}),
                                          m_listOfEdges ({}),
                                          m_listOfCells ({})
{
}

Point::Point (const Point & pointToCopy) : x (pointToCopy.x),
                                           y (pointToCopy.y),
                                           m_listOfPoints (pointToCopy.m_listOfPoints),
                                           m_listOfEdges (pointToCopy.m_listOfEdges),
                                           m_listOfCells (pointToCopy.m_listOfCells)
{
}

Point::~Point ()
{
    m_listOfPoints.clear ();
    m_listOfEdges.clear ();
    m_listOfCells.clear ();
}

// Accesseurs

LOC
Point::GetLoc ()
{
    return m_LOC;
}

Point *
Point::GetNeighPoint (int i)
{
    return m_listOfPoints [i];
}

Edge *
Point::GetNeighEdge (int i)
{
    return m_listOfEdges [i];
}

Cell *
Point::GetNeighCell (int i)
{
    return m_listOfCells [i];
}

int
Point::GetGlobalIndex ()
{
    return m_globalIndex;
}

// Changement d'attributs

void
Point::SetLOC (LOC loc)
{
    m_LOC = loc;
}

void
Point::SetGlobalIndex (int idx)
{
    m_globalIndex = idx;
}

// Insertion et retrait de connectivité
void
Point::InsertNeighPoint (Point * newPoint)
{
    if (newPoint == nullptr)
        return;

    for (Point * p : m_listOfPoints)
    {
        if (p == newPoint)
            return;
    }

    m_listOfPoints.push_back (newPoint);
}

void
Point::InsertNeighEdge (Edge * newEdge)
{
    if (newEdge == nullptr)
        return;

    for (Edge * e : m_listOfEdges)
    {
        if (e == newEdge)
            return;
    }

    m_listOfEdges.push_back (newEdge);
}

void
Point::InsertNeighCell (Cell * newCell)
{
    if (newCell == nullptr)
        return;

    for (Cell * c : m_listOfCells)
    {
        if (c == newCell)
            return;
    }

    m_listOfCells.push_back (newCell);
}

void
Point::RemoveNeighPoint (Point * pointOut)
{
    std::vector<Point *> newList = {};

    for (Point * p : m_listOfPoints)
    {
        if (p != pointOut)
            newList.push_back (p);
    }

    m_listOfPoints = newList;
}

void
Point::RemoveNeighEdge (Edge * edgeOut)
{
    std::vector<Edge *> newList = {};

    for (Edge * e : m_listOfEdges)
    {
        if (e != edgeOut)
            newList.push_back (e);
    }

    m_listOfEdges = newList;
}

void
Point::RemoveNeighCell (Cell * cellOut)
{
    std::vector<Cell *> newList = {};

    for (Cell * c : m_listOfCells)
    {
        if (c != cellOut)
            newList.push_back (c);
    }

    m_listOfCells = newList;
}

// Opérations sur les points

Point &
Point::operator+= (const Point & b)
{
    x += b.x;
    y += b.y;
    return *this;
}

Point &
Point::operator-= (const Point & b)
{
    x -= b.x;
    y -= b.y;
    return *this;
}

Point &
Point::operator*= (double k)
{
    x *= k;
    y *= k;
    return *this;
}

// LES FONCTIONS

Point
operator+ (const Point & a, const Point & b)
{
    Point res = a;
    res += b;
    return res;
}

Point
operator- (const Point & a, const Point & b)
{
    Point res = a;
    res -= b;
    return res;
}

Point
operator* (const Point & a, double k)
{
    Point res = a;
    res *= k;
    return res;
}

Point
operator* (double k, const Point & a)
{
    return a * k;
}
