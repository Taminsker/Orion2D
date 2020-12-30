
hf = 1e-5;
hg = 1e0;

// Point 1
Ox = 1; Oy = 0.1;
Point(1) = {Ox, Oy, 0, hf};

// Point 2/3
ax = 0.5;
ay = 0.0; day = 0.2;
Point(2) = {ax, ay, 0, hf};
Point(3) = {ax, ay + day, 0, hf};

// Point 4/5
bx = 0.0;
by = 0.2; dby = 0.2;
Point(4) = {bx, by, 0, hf};
Point(5) = {bx, by+dby, 0, hf};

// Point 6/7
cx = -0.5;
cy = -0.3; dcy = 0.7;
Point(6) = {cx, cy, 0, hf};
Point(7) = {cx, cy + dcy, 0, hf};

// Box OUTSIDE
kx = 10; ky = 10;
Point(8) = {kx, ky, 0, hg};
Point(9) = {-kx, ky, 0, hg};
Point(10) = {-kx, -ky, 0, hg};
Point(11) = {kx, -ky, 0, hg};

Bezier(1) = {1, 2, 4, 6, 7, 5, 3, 1};
Line(2) = {8, 9};
Line(3) = {9, 10};
Line(4) = {10, 11};
Line(5) = {11, 8};

Mesh 1;

//+
Curve Loop(1) = {2, 3, 4, 5};
//+
Curve Loop(2) = {1};
//+
Plane Surface(1) = {1, 2};

