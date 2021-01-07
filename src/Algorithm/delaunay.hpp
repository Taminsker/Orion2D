#ifndef DELAUNAY_HPP
#define DELAUNAY_HPP

#include "../Core/core.hpp"

// Pour savoir si le point p est dans le cercle circonscrit à la cellule edge
bool
PointInCircle (Mesh *mesh, Point &p, ul_t id);

bool
PointInTriangle (Mesh *mesh, Point &p, ul_t id);

void
DelaunayKernel (Point &p, Mesh *output);

void
DelaunayTriangulation (Mesh *input, Mesh *output);

#endif  // DELAUNAY_HPP
