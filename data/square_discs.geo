// Gmsh project created on Mon Jan 11 02:42:42 2021
SetFactory("OpenCASCADE");
//+

h = 1e-1;

//+
Point(1) = {-0.6, 0.3, 0, h};
//+
Point(2) = {-0.3, 0.6, 0, h};
//+
Point(3) = {-0.4, 0.4, 0, h};
//+
Point(4) = {-0.5, 0.4, 0, h};

BSpline(1) = {1, 2, 3, 4, 1};
//+
Point(6) = {-0.5, 0.5, 0, h};
//+
Point(7) = {-0.5, 0.4, 0, h};
//+
Point(8) = {-0.5, 0.6, 0, h};
//+
Point(9) = {-0.4, 0.6, 0, h};
//+
Point(10) = {-0.6, 0.4, 0, h};
//+
Point(11) = {-0.6, 0.5, 0, h};


