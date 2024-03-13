#if __GFPoly_==285
#include <catch2/catch_test_macros.hpp>
#include "reedsolomon/encoder.hpp"

class TestRsEncoder : public rs::Encoder
{
public:
    TestRsEncoder(size_t rcc = 4)
        : rs::Encoder(rcc)
    {}
    gf::Poly testCalcPolySyn(gf::Poly const& poly)
    { return calcPolySyn(poly); }

    gf::Poly testCalcErrPos(gf::Poly const& syndromes)
    {
        polySyn = syndromes;
        return calcErrPos();
    }
    gf::Poly testCalcPolyLoc(gf::Poly const& errPos)
    {
        return calcPolyLoc(errPos);
    }
    gf::Poly testCalcPolyErr(gf::Poly const& polySyn,
                             gf::Poly const& polyLoc
                             )
    {
        this->polySyn = polySyn;
        this->polyLoc = polyLoc;
        return calcPolyErr();
    }

    gf::Poly testCalcMagnitudes(gf::Poly const& errPos,
                                gf::Poly const& polyLoc,
                                gf::Poly const& polyErr
                                )
    {
        this->polyLoc = polyLoc;
        this->polyErr = polyErr;
        return calcMagnitudes(errPos);
    }
};

TEST_CASE_METHOD(TestRsEncoder, "Testing reedsolomon calcPolySyn()","[check]")
{
    CHECK( testCalcPolySyn(
               gf::Poly({0xDB, 0x22, 0x58, 0x5C, 0x44, 0x4F, 0x4E, 0x27,
                         0x54, 0x20, 0x50, 0x41, 0x4E, 0x49, 0x42})
               )
           == gf::Poly({0x13, 0x18, 0xB5, 0x5D})
           );

    CHECK( testCalcPolySyn(
               gf::Poly({0xDB, 0x22, 0x58, 0x5C, 0x44, 0x4F, 0x4E, 0x27,
                         0x54, 0x20, 0x50, 0x41, 0x4E, 0x49, 0x43})
               )
           == gf::Poly({0x00, 0x00, 0x00, 0x00})
           );

    CHECK( testCalcPolySyn(
               gf::Poly({0xDB, 0x22, 0x58, 0x5C, 0x44, 0x4F, 0x4E, 0x27,
                         0x54, 0x20, 0x41, 0x41, 0x41, 0x41, 0x41})
               )
           == gf::Poly({0x72, 0xBD, 0x22, 0x5B})
           );
}

TEST_CASE_METHOD(TestRsEncoder, "Testing reedsolomon calcPolyLoc()", "[check]")
{
    CHECK( testCalcPolyLoc( gf::Poly({0x0A, 0x0C, 0x0D, 0x0E}) )
           == gf::Poly({0x01, 0x2D, 0xA5, 0xC6, 0x8C})
           );
}

TEST_CASE_METHOD(TestRsEncoder, "Testing reedsolomon calcPolyErr()", "[check]")
{
    CHECK( testCalcPolyErr(
               gf::Poly({0x72, 0xBD, 0x22, 0x5B}),
               gf::Poly({0x01, 0x2D, 0xA5, 0xC6, 0x8C})
               )
           == gf::Poly({0x72, 0x4B, 0x10, 0x22})
           );
}

TEST_CASE_METHOD(TestRsEncoder, "Testing reedsolomon calcMagnitudes()", "[check]")
{
    CHECK( testCalcMagnitudes(
               gf::Poly({0x0A, 0x0C, 0x0D, 0x0E}),
               gf::Poly({0x01, 0x2D, 0xA5, 0xC6, 0x8C}),
               gf::Poly({0x72, 0x4B, 0x10, 0x22})
               )
           == gf::Poly({0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x11, 0x00, 0x0F, 0x08, 02})
           );
}

#endif//__GFPoly_==285
