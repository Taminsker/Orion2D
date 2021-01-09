#ifndef VORONOI_HPP
#define VORONOI_HPP

#include <vector>

#include "../Core/core.hpp"

real_t
EquilibrateKernel (Mesh *mesh, ul_t toexclude, std::vector<std::vector<idx_t>> &table);

void
EquilibrateByVoronoi (Mesh *mesh, ul_t toexclude);

#endif  // VORONOI_HPP
