#include "quality.hpp"

#include <iomanip>

#include "../Core/core.hpp"

// Qualité d'un triangle ABC en 2D
real_t
ComputeQuality (Cell *cell)
{
    if (cell->GetNumberOfPoints () != 3)
        return -1.;

    Point *pA = cell->GetPoint (0);
    Point *pB = cell->GetPoint (1);
    Point *pC = cell->GetPoint (2);

    real_t dAB = std::sqrt ((pB->x - pA->x) * (pB->x - pA->x) + (pB->y - pA->y) * (pB->y - pA->y));
    real_t dAC = std::sqrt ((pC->x - pA->x) * (pC->x - pA->x) + (pC->y - pA->y) * (pC->y - pA->y));
    real_t dBC = std::sqrt ((pC->x - pB->x) * (pC->x - pB->x) + (pC->y - pB->y) * (pC->y - pB->y));

    real_t sum = dAB * dAB + dAC * dAC + dBC * dBC;

    // Aire du triangle ABC = 0.5 * ||AB^AC|| = 0.5 * ||[0, 0, z_ABC]||

    // AB = u = [u0, u1]
    real_t u0 = pB->x - pA->x;
    real_t u1 = pB->y - pA->y;

    // AC = v = [v0, v1]
    real_t v0 = pC->x - pA->x;
    real_t v1 = pC->y - pA->y;

    // Composante z de AB^AC = u^v
    real_t z_ABC = u0 * v1 - u1 * v0;

    // Aire du triangle ABC (maille K)
    real_t volK = 0.5 * std::fabs (z_ABC);

    // ERROR << "volK " << volK << ENDLINE;
    return (std::sqrt (3.0) / (12.0 * volK)) * sum;
}

// Minimum, maximum, moyenne et répartition des qualités
void
MakeHistogram (std::vector<real_t> v)
{
    BEGIN << "Histogram of qualities" << ENDLINE;

    if (v.size () == 0)
    {
        WARNING << "qualities vector is empty !" << ENDLINE;
        ENDFUN;
        return;
    }
    real_t min = v [0], max = v [0], moy = 0.;
    int    over1 = 0, over2 = 0, over3 = 0, over5 = 0, over10 = 0, over50 = 0, over100 = 0;

    for (real_t value : v)
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

    moy /= v.size ();

    INFOS << "minimum = " << min << "." << std::endl;
    INFOS << "maximum = " << max << "." << std::endl;
    INFOS << "mean = " << moy << "." << std::endl;

    INFOS << "[1,2[      : " << SPC over1 << ", so " << SPC 100. * over1 / v.size () << "%." << std::endl;
    INFOS << "[2,3[      : " << SPC over2 << ", so " << SPC 100. * over2 / v.size () << "%." << std::endl;
    INFOS << "[3,5[      : " << SPC over3 << ", so " << SPC 100. * over3 / v.size () << "%." << std::endl;
    INFOS << "[5,10[     : " << SPC over5 << ", so " << SPC 100. * over5 / v.size () << "%." << std::endl;
    INFOS << "[10,50[    : " << SPC over10 << ", so " << SPC 100. * over10 / v.size () << "%." << std::endl;
    INFOS << "[50,100[   : " << SPC over50 << ", so " << SPC 100. * over50 / v.size () << "%." << std::endl;
    INFOS << "[100,+inf[ : " << SPC over100 << ", so " << SPC 100. * over100 / v.size () << "%." << std::endl;

    ENDFUN;
    return;
}
