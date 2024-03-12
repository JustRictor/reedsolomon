#if __GFPoly_ == 285
#include <catch2/catch_test_macros.hpp>
#include "reedsolomon/ghalua_byte.hpp"

TEST_CASE( "Testing ghalua sum GF[256] a=2 poly=285", "[require]" )
{
    REQUIRE( gf::Byte(  6) + gf::Byte(  3) == gf::Byte(  5) );
    REQUIRE( gf::Byte( 10) + gf::Byte(  5) == gf::Byte( 15) );
    REQUIRE( gf::Byte(  3) + gf::Byte( 19) == gf::Byte( 16) );
    REQUIRE( gf::Byte(  8) + gf::Byte(  0) == gf::Byte(  8) );
    REQUIRE( gf::Byte( 11) + gf::Byte(  6) == gf::Byte( 13) );
    REQUIRE( gf::Byte(  7) + gf::Byte(  0) == gf::Byte(  7) );
    REQUIRE( gf::Byte(255) + gf::Byte(255) == gf::Byte(  0) );
    REQUIRE( gf::Byte(243) + gf::Byte(  0) == gf::Byte(243) );
}

TEST_CASE( "Testing ghalua mult GF[256] a=2 poly=285", "[require]")
{
    REQUIRE( gf::Byte( 17) * gf::Byte(200) == gf::Byte(212) );
    REQUIRE( gf::Byte(  8) * gf::Byte(  6) == gf::Byte( 48) );
    REQUIRE( gf::Byte(  8) * gf::Byte( 11) == gf::Byte( 88) );
    REQUIRE( gf::Byte(  9) * gf::Byte(  6) == gf::Byte( 54) );
    REQUIRE( gf::Byte(  9) * gf::Byte( 11) == gf::Byte( 83) );
    REQUIRE( gf::Byte(  2) * gf::Byte(  6) == gf::Byte( 12) );
    REQUIRE( gf::Byte(  2) * gf::Byte( 11) == gf::Byte( 22) );
    REQUIRE( gf::Byte(255) * gf::Byte(  0) == gf::Byte(  0) );
    REQUIRE( gf::Byte(  0) * gf::Byte(255) == gf::Byte(  0) );
}

TEST_CASE( "Testing ghalua div GF[256] a=2 poly=285", "require")
{
    REQUIRE( gf::Byte(212) / gf::Byte(200) == gf::Byte( 17) );
    REQUIRE( gf::Byte(212) / gf::Byte( 17) == gf::Byte(200) );
    REQUIRE( gf::Byte( 48) / gf::Byte(  6) == gf::Byte(  8) );
    REQUIRE( gf::Byte( 48) / gf::Byte(  8) == gf::Byte(  6) );
    REQUIRE( gf::Byte( 12) / gf::Byte(  6) == gf::Byte(  2) );
    REQUIRE( gf::Byte( 12) / gf::Byte(  2) == gf::Byte(  6) );
    try
    {
        gf::Byte(255) / gf::Byte(0);
        WARN("division by zero did not throw an exception");
        REQUIRE(false);
    }
    catch(std::invalid_argument){}
    REQUIRE( gf::Byte(  0) / gf::Byte(255) == gf::Byte(  0) );
}

TEST_CASE( "Testing ghalua pow GF[256] a=2 poly=285", "[require]")
{
    ///\todo fixme
}

#endif//__GFPoly_==285
