#include "swap.hpp"

#include <iostream>

// void SwapEdge (Triangle & tri1, Triangle & tri2)
//{
//    // Listes des indices des points appartenant à tri1 et tri2
//    std::vector<int> list1 (3);
//    std::vector<int> list2 (3);

//    for (int k = 0; k < 2; k++) {
//        list1 [k] = tri1 [k];
//        list2 [k] = tri2 [k];
//    }

//    // Indices des 2 points partagés par tri1 et tri2 : ils forment l'arête à supprimer
//    std::vector<int> commonPts = CommonPoints (list1, list2);
//    int com1 = commonPts [0], com2 = commonPts [1];

//    // Indices des 2 points partagés par tri1 et tri2 : ils forment l'arête à supprimer
//    std::vector<int> commonPts;
//    // Indices des 2 points non partagés par tri1 et tri2 : ils forment l'arête à créer
//    std::vector<int> diffPts;

//    for (int k : list1)
//    {
//        if (ElementInList (k, list2))
//            commonPts.push_back (k);

//        else
//            diffPts.push_back (k);
//    }

//    for (int k : list2)
//        if (! ElementInList (k, list1))
//            diffPts.push_back (k);

//    // Les 2 points partagés, et les 2 points non partagés
//    int com1  = commonPts [0], com2  = commonPts [1];
//    int diff1 = diffPts   [0], diff2 = diffPts   [1];

//    // Redistribution des points pour former les nouveaux triangles par swap d'arête
//    tri1 [0] = diff1, tri1 [1] = diff2, tri1 [2] = com1;
//    tri2 [0] = diff1, tri2 [1] = diff2, tri2 [2] = com2;

//    return;
//}

// bool ElementInList (int number, std::vector<int> & list)
//{
//    for (int k : list)
//        if (k == number)
//            return true;

//    return false;
//}
