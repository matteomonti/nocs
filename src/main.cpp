#ifdef __main__

#include <iostream>

#include "geometry/vec.h"
#include "molecule/molecule.h"

int main()
{
    std :: vector<atom> a;

    a.push_back(atom(vec(3, 4), 1, 1));
    a.push_back(atom(vec(-3, 4), 1, 1));
    a.push_back(atom(vec(0, 2), 1, 2));

    std :: cout << a[0] << a[1] << a[2];
}

#endif
