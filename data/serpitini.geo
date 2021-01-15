// Gmsh project created on Mon Jan 11 00:38:23 2021
SetFactory("OpenCASCADE");

h = 5e-2;

Point(1) = {0, 0, 0, h};

Point(2) = {1, 0, 0, h};

Point(3) = {0.8, 0, 0, h};

Point(4) = {0.6, 0, 0, h};

Point(5) = {0.4, 0, 0, h};

Point(6) = {0.2, 0, 0, h};

Point(7) = {-0.2, 0, 0, h};

Point(8) = {-0.4, 0, 0, h};

Point(9) = {-0.6, 0, 0, h};

Point(10) = {-0.8, 0, 0, h};

Point(11) = {-1, 0, 0, h};

Point(12) = {0, 1, 0, h};

Point(13) = {0, 0.9, 0, h};

Point(14) = {0, 0.7, 0, h};

Point(15) = {0, 0.5, 0, h};

Point(16) = {0, 0.3, 0, h};

Point(17) = {0, 0.1, 0, h};

Point(18) = {0, -0.1, 0, h};

Point(19) = {0, -0.3, 0, h};

Point(20) = {0, -0.5, 0, h};

Point(21) = {0, -0.7, 0, h};

Point(22) = {0, -0.9, 0, h};

Point(23) = {0, -1, 0, h};

Circle(1) = {2, 1, 12};

Circle(2) = {12, 1, 11};

Circle(3) = {11, 1, 23};

Circle(4) = {23, 1, 2};



Circle(5) = {13, 1, 22};

Circle(6) = {21, 1, 14};

Circle(7) = {15, 1, 20};

Circle(8) = {19, 1, 16};

Circle(9) = {10, 1, 3};

//Circle(10) = {3, 1, 9};

Circle(10) = {4, 1, 9};

Circle(11) = {8, 1, 5};

Circle(12) = {6, 1, 7};

Circle(13) = {17, 1, 18};

Line(14) = {14, 15};

Line(15) = {4, 3};

Line(16) = {21, 22};

Line(17) = {7, 1};

Line(18) = {17, 16};

Line(19) = {8, 9};

Line(20) = {6, 5};

Line(21) = {19, 20};

Line(22) = {1, 18};

Line(23) = {13, 12};

Line(24) = {10, 11};

Delete {
  Curve{3}; Curve{4}; Curve{1}; 
}


//+
Physical Curve(1) = {24, 9, 2, 6, 11, 8, 18, 13, 17, 22, 12, 7, 21, 19, 10, 5, 16, 20, 15, 14, 23};
