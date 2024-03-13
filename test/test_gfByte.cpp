#if __GFPoly_ == 285
#include <catch2/catch_test_macros.hpp>
#include "reedsolomon/ghalua_byte.hpp"

TEST_CASE( "Testing ghalua sum GF[256] a=2 poly=285", "[check]" )
{
    CHECK( gf::Byte(  6) + gf::Byte(  3) == gf::Byte(  5) );
    CHECK( gf::Byte( 10) + gf::Byte(  5) == gf::Byte( 15) );
    CHECK( gf::Byte(  3) + gf::Byte( 19) == gf::Byte( 16) );
    CHECK( gf::Byte(  8) + gf::Byte(  0) == gf::Byte(  8) );
    CHECK( gf::Byte( 11) + gf::Byte(  6) == gf::Byte( 13) );
    CHECK( gf::Byte(  7) + gf::Byte(  0) == gf::Byte(  7) );
    CHECK( gf::Byte(255) + gf::Byte(255) == gf::Byte(  0) );
    CHECK( gf::Byte(243) + gf::Byte(  0) == gf::Byte(243) );
}

TEST_CASE( "Testing ghalua mult GF[256] a=2 poly=285", "[check]")
{
    CHECK( gf::Byte( 17) * gf::Byte(200) == gf::Byte(212) );
    CHECK( gf::Byte(  8) * gf::Byte(  6) == gf::Byte( 48) );
    CHECK( gf::Byte(  8) * gf::Byte( 11) == gf::Byte( 88) );
    CHECK( gf::Byte(  9) * gf::Byte(  6) == gf::Byte( 54) );
    CHECK( gf::Byte(  9) * gf::Byte( 11) == gf::Byte( 83) );
    CHECK( gf::Byte(  2) * gf::Byte(  6) == gf::Byte( 12) );
    CHECK( gf::Byte(  2) * gf::Byte( 11) == gf::Byte( 22) );
    CHECK( gf::Byte(255) * gf::Byte(  0) == gf::Byte(  0) );
    CHECK( gf::Byte(  0) * gf::Byte(255) == gf::Byte(  0) );
}

TEST_CASE( "Testing ghalua div GF[256] a=2 poly=285", "[check]")
{
    CHECK( gf::Byte(212) / gf::Byte(200) == gf::Byte( 17) );
    CHECK( gf::Byte(212) / gf::Byte( 17) == gf::Byte(200) );
    CHECK( gf::Byte( 48) / gf::Byte(  6) == gf::Byte(  8) );
    CHECK( gf::Byte( 48) / gf::Byte(  8) == gf::Byte(  6) );
    CHECK( gf::Byte( 12) / gf::Byte(  6) == gf::Byte(  2) );
    CHECK( gf::Byte( 12) / gf::Byte(  2) == gf::Byte(  6) );
    try
    {
        gf::Byte(255) / gf::Byte(0);
        WARN("division by zero did not throw an exception");
        CHECK(false);
    }
    catch(std::invalid_argument){}
    CHECK( gf::Byte(  0) / gf::Byte(255) == gf::Byte(  0) );
}

TEST_CASE( "Testing ghalua pow GF[256] a=2 poly=285", "[check]")
{
    ///\todo fixme
}

#endif//__GFPoly_==285
