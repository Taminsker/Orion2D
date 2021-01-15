#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

#include <array>
#include <vector>

#include "../orionglobal.hpp"

// The object in the hash map
using triobj_t = std::array<idx_t, 2>;
using trimap_t = std::vector<std::vector<triobj_t>>;

class Mesh;

void
PropagateTheColor (trimap_t *triMap, std::vector<idx_t> *colored, ul_t idTri, idx_t color);

void
ForceBoundaries (Mesh *input, Mesh *mesh);

#endif  // BOUNDARY_HPP
