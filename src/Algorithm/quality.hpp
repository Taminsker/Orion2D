#ifndef SRC_ALGORITHM_QUALITY_HPP
#define SRC_ALGORITHM_QUALITY_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include "../orionheader.hpp"

class Cell;
class Mesh;

// Qualité d'un triangle ABC en 2D
double quality (Cell* cell);

// Minimum, maximum, moyenne et répartition des qualités
void histogram (std::vector<double> v);

// Renseigner le vecteur des qualités des éléments du maillage
void ComputeQualities (Mesh* mesh, std::vector<real_t> * qualities);

#endif /* SRC_ALGORITHM_QUALITY_HPP */
