#ifndef POINT_HPP
#define POINT_HPP

#include <vector>

#include "../Tools/smartpointer.hpp"
#include "../orionglobal.hpp"
#include "templates.h"

class Cell;
class Edge;

typedef enum
{
    INSIDE  = -1,
    BORDER  = 0,
    OUTSIDE = 1,
} LOC;

struct Point
{
    // Constructeurs et destructeur
    Point (real_t xval = 0., real_t yval = 0., real_t zval = 0.);
    Point (const Point &pointToCopy);
    //    ~Point () {}

    // Opérations sur les points
    Point &
    operator+= (const Point &b);

    Point &
    operator-= (const Point &b);

    Point &
    operator*= (real_t k);

    // Data
    // Coordonnées
    real_t x;
    real_t y;
    real_t z;

    // Indice dans la numérotation globale
    int globalIndex;

    // Localisation
    LOC loc;

    // Connectivité
    std::vector<Smart<Point>> points;  // Points voisins
    std::vector<Smart<Edge>>  edges;   // Arêtes auxquelles il appartient
    std::vector<Smart<Cell>>  cells;   // Cellules auxquelles il appartient
};

Point
operator+ (const Point &a, const Point &b);

Point
operator- (const Point &a, const Point &b);

Point
operator* (const Point &a, real_t k);

Point
operator* (real_t k, const Point &a);

#endif  // POINT_HPP
