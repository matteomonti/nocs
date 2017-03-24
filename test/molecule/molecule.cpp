#include "catch.hpp"

// Libraries

#include <iostream>

// Includes

#include "geometry/vec.h"
#include "molecule/molecule.h"

// Tests

TEST_CASE("Molecule initialize correctly and prints output", "[constructors] [printers]")
{
  SECTION("Initializing and printing")
  {
    std :: vector<atom> a;

    a.push_back(atom(vec(3, 4), 1, 1));
    a.push_back(atom(vec(-3, 4), 1, 1));
    a.push_back(atom(vec(0, 2), 1, 1));

    std :: cout << a[0] << a[1] << a[2];

    molecule m(a);

    std :: cout << m;

    std :: cout << m[0] << m[1] << m[2];

    REQUIRE(true == true);
  }
}
