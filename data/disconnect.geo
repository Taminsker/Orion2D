h1 = 1e-2;
h2 = 1e-1;

y = 0.8;

Point(1) = {0, 0, 0, h1};
Point(2) = {1, 0, 0, h1};
Point(3) = {1, 1, 0, h1};
Point(4) = {0, 1, 0, h1};

Point(5) = {1, y, 0, h1};
Point(6) = {2, y, 0, h1};
Point(7) = {2, 1+y, 0, h1};
Point(8) = {1, 1+y, 0, h1};

Line(1) = {1, 2};
Line(2) = {2, 5};
Line(3) = {5, 3};
Line(4) = {3, 4};
Line(5) = {4, 1};

Line(6) = {5, 6};
Line(7) = {6, 7};
Line(8) = {7, 8};
Line(9) = {8, 3};

Mesh 1;
