#ifndef SRC_IO_IO_HPP
#define SRC_IO_IO_HPP

#include <fstream>
#include <iomanip>
#include <iostream>

#include "../orionglobal.hpp"

struct Mesh;

void
Read (Mesh *mesh, std::string filename);

void
Write (Mesh *mesh, std::string filename);

#endif /* SRC_IO_IO_HPP */
