
h1 = 1e-1;
h2 = 1e-2;
n = 5;
r1 = 1.0;
r2 = 0.4;


angle = 2 * Pi / n;
For i In {1:n}
    Point(i) = {r1 * Cos(i * angle), r1 * Sin(i * angle), 0, h1};
    Point(i+n) = {r2 * Cos(i * angle + angle/2), r2 * Sin(i * angle + angle/2), 0, h2};
EndFor

Line(1) = {2 * n, 1};
Line(2) = {1, n+1};

For i In {2:n}
    Line(2 * i - 1) = {n+i-1, i};
    Line(2 * i) = {i, n+i};
EndFor

Mesh 1;