#ifndef SRC_DATA_POINT_HPP
#define SRC_DATA_POINT_HPP

#include <iostream>

typedef enum {
    BORDER = 0,
    INSIDE = 1,
} LOC;

class Point
{
public:
    // Coordonnées
    double x;
    double y;

    // Constructeurs et destructeur
    Point ();
    Point (double xval, double yval = 0.);
    Point (const Point& pointToCopy);
    ~Point ();

    // Accesseurs
    LOC GetLoc ();
    Point* GetNeighPoint  (int i);
    Edge*  GetNeighEdge   (int i);
    Cell*  GetNeighCell   (int i);
    int    GetGlobalIndex ();

    // Changement d'attributs
    void SetLOC         (LOC loc);
    void SetGlobalIndex (int idx);

    // Insertion et retrait de connectivité
    void InsertNeighPoint (Point* newPoint);
    void InsertNeighEdge  (Edge* newEdge);
    void InsertNeighCell  (Cell* newCell);

    void RemoveNeighPoint (Point* pointOut);
    void RemoveNeighEdge  (Edge* edgeOut);
    void RemoveNeighCell  (Cell* cellOut);

    // Opérations sur les points
    Point& operator+= (const Point& b);
    Point& operator-= (const Point& b);
    Point& operator*= (double k);

private:
    // Indice dans la numérotation globale
    int m_globalIndex;

    // Localisation
    LOC m_LOC;

    // Connectivité
    std::vector<Point*> m_listOfPoints; // Points voisins
    std::vector<Edge*>  m_listOfEdges;  // Arêtes auxquelles il appartient
    std::vector<Cell*>  m_listOfCells;  // Cellules auxquelles il appartient
};

Point operator+ (const Point& a, const Point& b);
Point operator- (const Point& a, const Point& b);
Point operator* (const Point& a, double k);
Point operator* (double k, const Point& a);

#endif /* SRC_DATA_POINT_HPP */
