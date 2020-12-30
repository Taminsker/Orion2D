#ifndef SRC_DATA_POINT_HPP
#define SRC_DATA_POINT_HPP

#include <iostream>
#include <vector>

#include "../orionheader.hpp"

class Cell;
class Edge;

typedef enum
{
    INSIDE  = -1,
    BORDER  = 0,
    OUTSIDE = 1,
} Loc;

class Point
{
public:
    // Coordonnées
    real_t x;
    real_t y;
    real_t z;

    // Constructeurs et destructeur
    Point (real_t xval = 0., real_t yval = 0., real_t zval = 0.);

    Point (const Point &pointToCopy);

    ~Point ();

    // Accesseurs
    Loc
    GetLoc ();

    Point *
    GetNeighPoint (ul_t i);

    Edge *
    GetNeighEdge (ul_t i);

    Cell *
    GetNeighCell (ul_t i);

    int
    GetGlobalIndex ();

    // Changement d'attributs
    void
    SetLoc (Loc loc);

    void
    SetGlobalIndex (int idx);

    // Insertion et retrait de connectivité
    void
    InsertNeighPoint (Point *newPoint);

    void
    InsertNeighEdge (Edge *newEdge);

    void
    InsertNeighCell (Cell *newCell);

    void
    RemoveNeighPoint (Point *pointOut);

    void
    RemoveNeighEdge (Edge *edgeOut);

    void
    RemoveNeighCell (Cell *cellOut);

    // Opérations sur les points
    Point &
    operator+= (const Point &b);

    Point &
    operator-= (const Point &b);

    Point &
    operator*= (real_t k);

private:
    // Indice dans la numérotation globale
    int m_globalIndex;

    // Localisation
    Loc m_loc;

    // Connectivité
    std::vector<Point *> m_listOfPoints;  // Points voisins
    std::vector<Edge *>  m_listOfEdges;   // Arêtes auxquelles il appartient
    std::vector<Cell *>  m_listOfCells;   // Cellules auxquelles il appartient
};

Point
operator+ (const Point &a, const Point &b);

Point
operator- (const Point &a, const Point &b);

Point
operator* (const Point &a, real_t k);

Point
operator* (real_t k, const Point &a);

#endif /* SRC_DATA_POINT_HPP */
