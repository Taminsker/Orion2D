#ifndef SRC_ALGORITHM_QUALITY_HPP
#define SRC_ALGORITHM_QUALITY_HPP

#include <iostream>
#include <cmath>
#include <vector>

class Cell;

// Qualité d'un triangle ABC en 2D
double quality (Cell* cell);

// Minimum, maximum, moyenne et répartition des qualités
void histogram (vector<double> v);

#endif /* SRC_ALGORITHM_QUALITY_HPP */
