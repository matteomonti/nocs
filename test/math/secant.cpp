#include "catch.hpp"

// Libraries

#include <cmath>

// Includes

#include "math/secant.hpp"

// Tests

TEST_CASE("Secant computes correctly the zero of a monotone function.")
{
    SECTION("Initializing and computing")
    {
        auto f = [&](const double & x)
        {
            return pow(x, 2) - 1.;
        };
        
        REQUIRE(fabs(secant :: compute(f, -3, 0) + 1) <= secant :: epsilon);
        
        auto g = [&](const double & x)
        {
            return -x;
        };
        
        REQUIRE(fabs(secant :: compute(g, -10, 52)) <= secant :: epsilon);
        
        auto h = [&](const double & x)
        {
            return -pow(x, 3) - 1;
        };
        
        REQUIRE(fabs(secant :: compute(h, -3, +10) + 1) <= secant :: epsilon);
    }
}