#ifndef SRC_ALGORITHM_DELAUNAY_HPP
#define SRC_ALGORITHM_DELAUNAY_HPP

class Point;
class Mesh;

void DelaunayOne (Point * p, Mesh * output);

void DelaunayTriangulation (Mesh * input, Mesh * output);

#endif /* SRC_ALGORITHM_DELAUNAY_HPP */
