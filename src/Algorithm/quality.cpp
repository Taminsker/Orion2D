#include "quality.hpp"

#include "../Core/core.hpp"

// Qualité d'un triangle ABC en 2D
double
quality (Cell * cell)
{
    if (cell->GetNumberOfPoints () != 3)
        return -1.;

    Point * pA = cell->GetPoint (0);
    Point * pB = cell->GetPoint (1);
    Point * pC = cell->GetPoint (2);

    double dAB = std::sqrt ((pB->x - pA->x) * (pB->x - pA->x) + (pB->y - pA->y) * (pB->y - pA->y));
    double dAC = std::sqrt ((pC->x - pA->x) * (pC->x - pA->x) + (pC->y - pA->y) * (pC->y - pA->y));
    double dBC = std::sqrt ((pC->x - pB->x) * (pC->x - pB->x) + (pC->y - pB->y) * (pC->y - pB->y));

    double sum = dAB * dAB + dAC * dAC + dBC * dBC;

    // Aire du triangle ABC = 0.5 * ||AB^AC|| = 0.5 * ||[0, 0, z_ABC]||

    // AB = u = [u0, u1]
    double u0 = pB->x - pA->x;
    double u1 = pB->y - pA->y;

    // AC = v = [v0, v1]
    double v0 = pC->x - pA->x;
    double v1 = pC->y - pA->y;

    // Composante z de AB^AC = u^v
    double z_ABC = u0 * v1 - u1 * v0;

    // Aire du triangle ABC (maille K)
    double volK = 0.5 * std::fabs (z_ABC);

    // ERROR << "volK " << volK << ENDLINE;
    return (std::sqrt (3.0) / (12.0 * volK)) * sum;
}

// Minimum, maximum, moyenne et répartition des qualités
void
histogram (std::vector<double> v)
{
    BEGIN << "Histogram of qualities" << ENDLINE;

    double min = v [0], max = v [0], moy = 0.;
    int    over1 = 0, over2 = 0, over3 = 0, over5 = 0, over10 = 0, over50 = 0, over100 = 0;

    for (double value : v)
    {
        moy += value;

        if (value < min)
            min = value;

        if (value > max)
            max = value;

        if (value >= 1 && value < 2)
            over1++;
        else if (value >= 2 && value < 3)
            over2++;
        else if (value >= 3 && value < 5)
            over3++;
        else if (value >= 5 && value < 10)
            over5++;
        else if (value >= 10 && value < 50)
            over10++;
        else if (value >= 50 && value < 100)
            over50++;
        else if (value >= 100)
            over100++;
    }

    moy /= static_cast<real_t> (v.size ());

    std::cout << "Qualité minimum = " << min << "." << std::endl;
    std::cout << "Qualité maximum = " << max << "." << std::endl;
    std::cout << "Qualité moyenne = " << moy << "." << std::endl;

    std::cout << "Qualités dans [1,2[      : " << over1 << ", soit " << 100. * over1 / v.size () << " %." << std::endl;
    std::cout << "Qualités dans [2,3[      : " << over2 << ", soit " << 100. * over2 / v.size () << " %." << std::endl;
    std::cout << "Qualités dans [3,5[      : " << over3 << ", soit " << 100. * over3 / v.size () << " %." << std::endl;
    std::cout << "Qualités dans [5,10[     : " << over5 << ", soit " << 100. * over5 / v.size () << " %." << std::endl;
    std::cout << "Qualités dans [10,50[    : " << over10 << ", soit " << 100. * over10 / v.size () << " %." << std::endl;
    std::cout << "Qualités dans [50,100[   : " << over50 << ", soit " << 100. * over50 / v.size () << " %." << std::endl;
    std::cout << "Qualités dans [100,+inf[ : " << over100 << ", soit " << 100. * over100 / v.size () << " %." << std::endl;

    ENDFUN;
    return;
}
