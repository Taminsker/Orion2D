h = 1e-2;
r = 0.4;

Point(1) = {r, 0, 0, h};
Point(2) = {0, r, 0, h};
Point(3) = {-r, 0, 0, h};
Point(4) = {0, -r, 0, h};

Point(5) = {0, 0, 0, 1.0};

Circle(1) = {2, 5, 3};
Circle(2) = {3, 5, 4};
Circle(3) = {4, 5, 1};
Circle(4) = {1, 5, 2};

Mesh 1;