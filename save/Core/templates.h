#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <algorithm>
#include <functional>
#include <vector>

#include "../Tools/smartpointer.hpp"
#include "../orionglobal.hpp"

struct Point;
struct Cell;
struct Edge;
struct Mesh;

struct OrionBase
{
    std::vector<Smart<Point>> points = {};  //! List of points
    std::vector<Smart<Cell>>  cells  = {};  //! List of cells
    std::vector<Smart<Edge>>  edges  = {};  //! List of edges

    virtual ~OrionBase () {}

    virtual void
    PurgeInvalid ()
    {
        PurgeInvalidInVector (points);
        PurgeInvalidInVector (cells);
        PurgeInvalidInVector (edges);

        return;
    }

    virtual void
    ClearAllMembers ()
    {
        points.clear ();
        cells.clear ();
        edges.clear ();

        return;
    }
};

typedef enum
{
    INSIDE  = -1,
    BORDER  = 0,
    OUTSIDE = 1,
} LOC;

struct BasePoint
{
    real_t x           = 0.;       // Coordonnée x
    real_t y           = 0.;       // Coordonnée y
    real_t z           = 0.;       // Coordonnée z
    int    globalIndex = 0;        // Indice dans la numérotation globale
    LOC    loc         = OUTSIDE;  // Localisation
};

struct Point : OrionBase, BasePoint
{
};

struct Cell : OrionBase
{
};
struct Edge : OrionBase
{
};

struct Mesh : OrionBase
{
    ~Mesh () override { ClearAllMembers (); }

    void
    PurgeInvalid () override
    {
        std::for_each (std::begin (points), std::end (points), std::mem_fn (&OrionBase::PurgeInvalid));
        std::for_each (std::begin (cells), std::end (cells), std::mem_fn (&OrionBase::PurgeInvalid));
        std::for_each (std::begin (edges), std::end (edges), std::mem_fn (&OrionBase::PurgeInvalid));

        return OrionBase::PurgeInvalid ();
    }

    void
    ClearAllMembers () override
    {
        std::for_each (std::begin (points), std::end (points), std::mem_fn (&OrionBase::ClearAllMembers));
        std::for_each (std::begin (cells), std::end (cells), std::mem_fn (&OrionBase::ClearAllMembers));
        std::for_each (std::begin (edges), std::end (edges), std::mem_fn (&OrionBase::ClearAllMembers));

        return OrionBase::ClearAllMembers ();
    }
};

// Connect part
#define CONNECT(TYPE1, TYPE2, CONT1, CONT2)                                                                            \
    template <>                                                                                                        \
    void Connect (Smart<TYPE1> &obj, std::vector<Smart<TYPE2>> list)                                                   \
    {                                                                                                                  \
        std::copy (std::begin (list), std::end (list), std::back_inserter (obj->CONT1));                               \
        std::for_each (list.begin (), list.end (), [obj] (Smart<Point> &cursor) { cursor->CONT2.push_back (obj); });   \
        return;                                                                                                        \
    }

template <typename T, typename U>
void
Connect (Smart<T> &obj, std::vector<Smart<U>> list);

CONNECT (Point, Point, points, points)
CONNECT (Point, Cell, cells, points)
CONNECT (Point, Edge, edges, points)

CONNECT (Cell, Point, points, cells)
CONNECT (Cell, Cell, cells, cells)
CONNECT (Cell, Edge, edges, cells)

CONNECT (Edge, Point, points, edges)
CONNECT (Edge, Cell, cells, edges)

#undef CONNECT

#endif  // TEMPLATES_H
