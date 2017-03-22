#include "catch.hpp"

TEST_CASE("I know what one plus one is")
{
    SECTION("Actually doing my first test!")
    {
        REQUIRE(1+1 == 2);
    }
    
    SECTION("Let us go further!")
    {
        REQUIRE(2+2 == 4);
    }
}
