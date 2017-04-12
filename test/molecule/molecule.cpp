#include "catch.hpp"

// Libraries

#include <iostream>
#include <sstream>

// Includes

#include "geometry/vec.h"
#include "molecule/molecule.h"

// Tests

TEST_CASE("Molecule initialize correctly and prints output", "[constructors] [printers]")
{
  SECTION("Initializing and printing")
  {
    std :: vector<atom> a;

    a.push_back(atom({3, 4}, 1, 1));
    a.push_back(atom({-3, 4}, 1, 1));
    a.push_back(atom({0, 2}, 2, 1));

    molecule m(a);

    // Redirect cout output to stream buffer to avoid logging

    std :: streambuf * ob = std :: cout.rdbuf();
    std :: stringstream ss;
    std :: cout.rdbuf(ss.rdbuf());

    std :: cout << a[0] << a[1] << a[2];
    std :: cout << m;
    std :: cout << m[0] << m[1] << m[2];

    // Restore cout output

    std :: cout.rdbuf(ob);

    REQUIRE(m[0].position() == vec(3., 1.));
    REQUIRE(m[1].position() == vec(-3., 1.));
    REQUIRE(m[2].position() == vec(0, -1.));

    REQUIRE(m.inertia_moment() == 24.);
    REQUIRE(m.mass() == 4.);
  }
}
