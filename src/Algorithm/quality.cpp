#include "quality.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../orionglobal.hpp"

// Minimum, maximum, moyenne et répartition des qualités
void
MakeHistogram (Mesh *mesh)
{
    BEGIN << "Histogram of qualities" << ENDLINE;

    std::vector<real_t> &v = mesh->qualities;

    if (v.size () == 0)
    {
        WARNING << "qualities vector is empty !" << ENDLINE;
        ENDFUN;
        return;
    }

    real_t min = v [0], max = v [0], moy = 0.;
    ul_t   over1 = 0, over2 = 0, over3 = 0, over5 = 0, over10 = 0, over50 = 0, over100 = 0;

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

    moy /= static_cast<real_t> (v.size ());

    INFOS << "count      : " << SPC v.size () << ENDLINE;
    INFOS << "minimum    : " << SPC min << ENDLINE;
    INFOS << "maximum    : " << SPC max << ENDLINE;
    INFOS << "mean       : " << SPC moy << ENDLINE;

    std::cout << std::endl;

    auto fun = [v] (ul_t num) -> real_t { return 100. * static_cast<real_t> (num) / static_cast<real_t> (v.size ()); };

    INFOS << "[1,2[      : " << SPC over1 << ", so " << SPC fun (over1) << " %" << ENDLINE;
    INFOS << "[2,3[      : " << SPC over2 << ", so " << SPC fun (over2) << " %" << ENDLINE;
    INFOS << "[3,5[      : " << SPC over3 << ", so " << SPC fun (over3) << " %" << ENDLINE;
    INFOS << "[5,10[     : " << SPC over5 << ", so " << SPC fun (over5) << " %" << ENDLINE;
    INFOS << "[10,50[    : " << SPC over10 << ", so " << SPC fun (over10) << " %" << ENDLINE;
    INFOS << "[50,100[   : " << SPC over50 << ", so " << SPC fun (over50) << " %" << ENDLINE;
    INFOS << "[100,+inf[ : " << SPC over100 << ", so " << SPC fun (over100) << " %" << ENDLINE;

    ENDFUN;
    return;
}
