#include "quality.hpp"
#include "../Core/core.hpp"

// Qualité d'un triangle ABC en 2D (attention : changements en 3D !!)
double quality (Cell* cell)
{
    if (cell->GetNumberOfPoints () != 3)
        return -1.;

    Point* pA = cell->GetPoint (0);
    Point* pB = cell->GetPoint (1);
    Point* pC = cell->GetPoint (2);

    // En 3D, rajouter les composantes z
    double dAB = sqrt((pB->x - pA->x) * (pB->x - pA->x) + (pB->y - pA->y) * (pB->y - pA->y));
    double dAC = sqrt((pC->x - pA->x) * (pC->x - pA->x) + (pC->y - pA->y) * (pC->y - pA->y));
    double dBC = sqrt((pC->x - pB->x) * (pC->x - pB->x) + (pC->y - pB->y) * (pC->y - pB->y));

    double sum = dAB*dAB + dAC*dAC + dBC*dBC;

    /* Aire du triangle ABC = 0.5 * ||AB^AC|| = 0.5 * ||[0, 0, z_ABC]||
    Attention : en 3D, AB^AC n'est pas forcément selon (Oz) !! Calculer AB^AC... */

    // AB = u = [u0, u1]
    double u0 = pB->x - pA->x;
    double u1 = pB->y - pA->y;
    // AC = v = [v0, v1]
    double v0 = pC->x - pA->x;
    double v1 = pC->y - pA->y;
    // Composante z de AB^AC = u^v
    double z_ABC = u0 * v1 - u1 * v0;
    // Aire du triangle ABC (maille K)
    double volK = 0.5 * fabs(z_ABC);

    return (sqrt(3) / (12*volK)) * sum;
}

// Minimum, maximum, moyenne et répartition des qualités
void histogram (std::vector<double> v)
{
    double min = v [0], max = v [0], moy = 0.;
    int over1 = 0, over2 = 0, over3 = 0, over5 = 0, over10 = 0, over50 = 0, over100 = 0;

    for (size_t k = 0; k < v.size (); ++k)
    {
        moy += v [k];
        if (v [k] < min) {min = v [k];}
        if (v [k] > max) {max = v [k];}
        if (v [k] >= 1  && v [k] < 2)   {over1++;}
        if (v [k] >= 2  && v [k] < 3)   {over2++;}
        if (v [k] >= 3  && v [k] < 5)   {over3++;}
        if (v [k] >= 5  && v [k] < 10)  {over5++;}
        if (v [k] >= 10 && v [k] < 50)  {over10++;}
        if (v [k] >= 50 && v [k] < 100) {over50++;}
        if (v [k] >= 100)               {over100++;}
    }

    moy /= v.size ();

    std::cout << "\nQualité minimum = " << min << "." << std::endl;
    std::cout << "\nQualité maximum = " << max << "." << std::endl;
    std::cout << "\nQualité moyenne = " << moy << "." << std::endl;

    std::cout << "\nQualités dans [1,2[      : " << over1   << ", soit " << 100.*over1/v.size ()   << " %." << std::endl;
    std::cout << "\nQualités dans [2,3[      : " << over2   << ", soit " << 100.*over2/v.size ()   << " %." << std::endl;
    std::cout << "\nQualités dans [3,5[      : " << over3   << ", soit " << 100.*over3/v.size ()   << " %." << std::endl;
    std::cout << "\nQualités dans [5,10[     : " << over5   << ", soit " << 100.*over5/v.size ()   << " %." << std::endl;
    std::cout << "\nQualités dans [10,50[    : " << over10  << ", soit " << 100.*over10/v.size ()  << " %." << std::endl;
    std::cout << "\nQualités dans [50,100[   : " << over50  << ", soit " << 100.*over50/v.size ()  << " %." << std::endl;
    std::cout << "\nQualités dans [100,+inf[ : " << over100 << ", soit " << 100.*over100/v.size () << " %." << std::endl;
}
