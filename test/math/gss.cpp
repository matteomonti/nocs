#include "catch.hpp"

// Libraries

#include <cmath>
#include <iostream>

// Includes

#include "math/gss.hpp"

// Tests

TEST_CASE("Gss computes correctly the extremum of a strictly unimodal function.")
{
    SECTION("Initializing and computing")
    {
        auto f = [&](const double & x)
        {
            return pow(x, 2);
        };
        
        
        REQUIRE(fabs(gss :: max(f, 1, 2) - 2) <= gss :: epsilon);
        REQUIRE(fabs(gss :: min(f, 1, 2) - 1) <= gss :: epsilon);
        REQUIRE(fabs(gss :: max(f, -1, 2) - 2) <= gss :: epsilon);
        REQUIRE(fabs(gss :: min(f, -2, 2)) <= gss :: epsilon);
    }
}