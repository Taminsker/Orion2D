#include "cavity.hpp"

// Pour savoir si le point p est dans le cercle circonscrit à la cellule edge
bool PointInCircle (Point* p, Cell* cell)
{
    bool inside = false; // Par défaut, on suppose que p est hors du cercle
    double x0, y0, r; // Cercle circonscrit de centre (x0,y0) et de rayon r

    Point* pA = cell->GetPoint (0);
    Point* pB = cell->GetPoint (1);
    Point* pC = cell->GetPoint (2);

    // Pour résoudre à la main le système : [[a,b],[c,d]] [x0,y0] = [f,g]
    double a = pB->x - pA->x;
    double b = pB->y - pA->y;
    double c = pC->x - pA->x;
    double d = pC->y - pA->y;
    double f = a * ((pA->x + pB->x) / 2.) + b * ((pA->y + pB->y) / 2.);
    double g = c * ((pA->x + pC->x) / 2.) + d * ((pA->y + pC->y) / 2.);
    double det = a * d - b * c;

    x0 = (d * f - b * g) / det;
    y0 = (a * g - c * f) / det;
    r = sqrt((pA->x - x0) * (pA->x - x0) + (pA->y - y0) * (pA->y - y0));

    double dist_PO = sqrt((p->x - x0) * (p->x - x0) + (p->y - y0) * (p->y - y0));

    if (dist_PO < r)
        inside = true;

    return inside;
}
