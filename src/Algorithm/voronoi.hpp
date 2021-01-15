#ifndef VORONOI_HPP
#define VORONOI_HPP

#include <vector>

#include "../Core/core.hpp"

// Barycenters
real_t
EquilibrateKernelBarycenters (Mesh *mesh, ul_t toexclude, std::vector<std::vector<idx_t>> &table);

void
EquilibrateByVoronoiBarycenters (Mesh *mesh, ul_t toexclude);

// Centroids
real_t
EquilibrateKernelCentroids (Mesh *mesh, ul_t toexclude, std::vector<std::vector<idx_t>> &table);

void
EquilibrateByVoronoiCentroids (Mesh *mesh, ul_t toexclude);

// Custom
real_t
EquilibrateKernelCustom (Mesh *mesh, ul_t toexclude, std::vector<std::vector<idx_t>> &table);

void
EquilibrateByVoronoiCustom (Mesh *mesh, ul_t toexclude);

#endif  // VORONOI_HPP
