#ifndef SRC_ALGORITHM_QUALITY_HPP
#define SRC_ALGORITHM_QUALITY_HPP

#include <cmath>
#include <iostream>
#include <vector>

class Cell;

// Qualité d'un triangle ABC en 2D
double
ComputeQuality (Cell *cell);

// Minimum, maximum, moyenne et répartition des qualités
void
MakeHistogram (std::vector<double> v);

#endif /* SRC_ALGORITHM_QUALITY_HPP */
