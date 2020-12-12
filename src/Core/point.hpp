#ifndef SRC_DATA_POINT_HPP
#define SRC_DATA_POINT_HPP

#include <iostream>
#include <vector>

class Cell;
class Edge;

typedef enum
{
    INSIDE = -1,
    BORDER = 0,
    OUTSIDE = 1,
} Loc;

class Point
{
public:
    // Coordonnées
    double x;
    double y;
    double z;

    // Constructeurs et destructeur
    Point (double xval = 0., double yval = 0., double zval = 0.);
    Point (const Point & pointToCopy);
    ~Point ();

    // Accesseurs
    Loc     GetLoc ();
    Point * GetNeighPoint (int i);
    Edge *  GetNeighEdge (int i);
    Cell *  GetNeighCell (int i);
    int     GetGlobalIndex ();

    // Changement d'attributs
    void SetLoc (Loc loc);
    void SetGlobalIndex (int idx);

    // Insertion et retrait de connectivité
    void InsertNeighPoint (Point * newPoint);
    void InsertNeighEdge (Edge * newEdge);
    void InsertNeighCell (Cell * newCell);

    void RemoveNeighPoint (Point * pointOut);
    void RemoveNeighEdge (Edge * edgeOut);
    void RemoveNeighCell (Cell * cellOut);

    // Opérations sur les points
    Point & operator+= (const Point & b);
    Point & operator-= (const Point & b);
    Point & operator*= (double k);

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

Point operator+ (const Point & a, const Point & b);
Point operator- (const Point & a, const Point & b);
Point operator* (const Point & a, double k);
Point operator* (double k, const Point & a);

#endif /* SRC_DATA_POINT_HPP */
