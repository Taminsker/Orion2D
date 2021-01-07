h1 = 1e-1;
h2 = 5e-1;
r1 = 0.4;
r2 = 1.0;

Point(1) = {r1, 0, 0, h1};
Point(2) = {0, r1, 0, h1};
Point(3) = {-r1, 0, 0, h1};
Point(4) = {0, -r1, 0, h1};

Point(5) = {r2, 0, 0, h2};
Point(6) = {0, r2, 0, h2};
Point(7) = {-r2, 0, 0, h2};
Point(8) = {0, -r2, 0, h2};

Point(9) = {0, 0, 0, 1.0};

Circle(1) = {2, 9, 3};
Circle(2) = {3, 9, 4};
Circle(3) = {4, 9, 1};
Circle(4) = {1, 9, 2};

Circle(5) = {6, 9, 7};
Circle(6) = {7, 9, 8};
Circle(7) = {8, 9, 5};
Circle(8) = {5, 9, 6};

Mesh 1;
