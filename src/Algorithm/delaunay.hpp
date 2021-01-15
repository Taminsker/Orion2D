#ifndef DELAUNAY_HPP
#define DELAUNAY_HPP

#include "../Core/core.hpp"

// Pour savoir si le point p est dans le cercle circonscrit à la cellule edge
bool
PointInCircTri (Mesh *mesh, Point &p, ul_t id);

bool
PointInTriangle (Mesh *mesh, Point &p, ul_t id);

ul_t
DelaunayKernel (Point &p, Mesh *output);

void
DelaunayTriangulation (Mesh *input, Mesh *output);

void
CheckDelaunayCriterion (Mesh *mesh);

void
InsertMasscenter (Mesh *input, Mesh *output, ul_t maxiter = 100);

#endif  // DELAUNAY_HPP
