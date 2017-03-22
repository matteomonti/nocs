#include "catch.hpp"

TEST_CASE("I know what one plus one is")
{
    SECTION("Actually doing my first test!")
    {
        REQUIRE(1+1 == 2);
    }
}
