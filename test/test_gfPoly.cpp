#if __GFPoly_==285
#include <catch2/catch_test_macros.hpp>
#include "reedsolomon/ghalua_poly.hpp"

TEST_CASE("Testing ghalua poly sum GF[256] a=2 poly=285" ,"[require]")
{
    REQUIRE( gf::Poly({3,8,11,7}) + gf::Poly({19,0,6})
             == gf::Poly({16,8,13,7})
             );
}

TEST_CASE("Testing ghalua poly mult GF[256] a=2 poly=285", "[require]")
{
    REQUIRE( gf::Poly({8,9,2}) * gf::Poly({6,11})
             == gf::Poly({48,110,95,22})
             );
}

TEST_CASE("Testing ghalua poly div GF[256] a=2 poly=285", "[require]")
{
    REQUIRE( gf::Poly({67,86,136,68}) / gf::Poly({6,11,7})
             == gf::Poly({9,87})
             );
}

TEST_CASE("Testing ghalua poly shift GF[256] a=2 poly=285", "[require]")
{
    REQUIRE( gf::Poly({14,12,13}) >> 2 == gf::Poly({0,0,14,12,13}));
    REQUIRE( gf::Poly({13,1,12,3}) << 2 == gf::Poly({12,3}));
}

#endif//__GFPoly_==285
