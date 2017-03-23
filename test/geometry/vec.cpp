#include "catch.hpp"

// Includes

#include "geometry/vec.h"

// Tests

TEST_CASE("Vector operators respects standard algebra", "[operators]")
{
  SECTION("Opposite")
  {
    vec v1(2, 3);
    vec v2 = -v1;

    REQUIRE(v1.x == -v2.x);
    REQUIRE(v1.y == -v2.y);
  }

  SECTION("Addition")
  {
    vec v1(2, 3);
    vec v2(4, 5);
    vec v3 = v1 + v2;

    REQUIRE(v3.x == 6);
    REQUIRE(v3.y == 8);

    v1 += v2;

    REQUIRE(v1.x == 6);
    REQUIRE(v1.y == 8);
  }

  SECTION("Subtraction")
  {
    vec v1(4, 5);
    vec v2(1, 3);
    vec v3 = v1 - v2;

    REQUIRE(v3.x == 3);
    REQUIRE(v3.y == 2);

    v1 -= v2;

    REQUIRE(v1.x == 3);
    REQUIRE(v1.y == 2);
  }

  SECTION("Multiplication with Double")
  {
    vec v1 (3, 6);
    double i = 2.0;
    vec v2 = v1 * i;
    vec v3 = i * v1; // Check External Operator
    v1 *= i;

    REQUIRE(v1.x == 6);
    REQUIRE(v1.y == 12);
    REQUIRE(v2.x == 6);
    REQUIRE(v2.y == 12);
    REQUIRE(v3.x == 6);
    REQUIRE(v3.y == 12);
  }

  SECTION("Division with Double")
  {
    vec v1 (4, 8);
    double i = 2.0;
    vec v2 = v1 / i;
    v1 /= i;

    REQUIRE(v1.x == 2);
    REQUIRE(v1.y == 4);
    REQUIRE(v2.x == 2);
    REQUIRE(v2.y == 4);
  }

  SECTION("Cross Product")
  {
    vec v1 (2, 3);
    vec v2 (5, 4);

    REQUIRE((v1 ^ v2) == (8 - 15));
    REQUIRE((v2 ^ v1) == (15 - 8));
  }

  SECTION("Scalar Product")
  {
    vec v1 (2, 3);
    vec v2 (5, 4);

    REQUIRE(v1 * v2 == 2*5 + 3*4);
  }

  SECTION("Squared Module")
  {
    vec v1 (3, 4);

    REQUIRE(~v1 == 25);
  }

  SECTION("Module")
  {
    vec v1 (3, 4);

    REQUIRE(!v1 == 5);
  }
}
