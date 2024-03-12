#include "reedsolomon/encoder.hpp"

rs::Encoder::Encoder(size_t _redundantCharCount)
    : redundantCharCount(_redundantCharCount == 0 ? 1
                                                  : _redundantCharCount
                         )
{
    if(_redundantCharCount == 0)
    {//должно быть другое разрешение ошибки
        std::cerr << "\nreedsolomonlib [WARNING] "
                     "number of redundant characters cannot be zero, replaced by 1\n";
    }
    if(polyGenerators.find(redundantCharCount) != polyGenerators.cend())
        return;
    gf::Poly polyGenerator({gf::Byte(2).pow(1), gf::Byte(1)});
    for(size_t i = 1; i < redundantCharCount; i++)
    {
        polyGenerator *= gf::Poly({gf::Byte(2).pow(i+1),gf::Byte(1)});
    }
    polyGenerators[redundantCharCount] = polyGenerator;
}

gf::Poly rs::Encoder::encode(const gf::Poly &poly) const
{
    return (poly >> redundantCharCount)
            + (poly >> redundantCharCount) / polyGenerators[redundantCharCount];
}

gf::Poly rs::Encoder::decode(const gf::Poly &poly) const
{
    gf::Poly polySyn = calcPolySyn(poly);
    if( polySyn == gf::Poly( std::vector<gf::Byte>(redundantCharCount,0) ) )
        return poly << redundantCharCount;
    throw std::logic_error("not implemented");
}

gf::Poly rs::Encoder::calcPolySyn(const gf::Poly &poly) const noexcept
{
    gf::Poly polySyn{};
    gf::Byte _x{2};
    for(size_t i = 0; i < redundantCharCount; i++)
        polySyn.push_back(poly(_x));
    return polySyn;
}

gf::Poly rs::Encoder::calcPolyLoc(const gf::Poly &errPos) const noexcept
{
    gf::Poly polyLoc(
                { 1, gf::Byte(2).pow(static_cast<uint8_t>(errPos[0])) }
                );
    for(auto it = errPos.cbegin() + 1; it != errPos.cend(); it++)
        polyLoc *= gf::Poly( { 1, gf::Byte(2).pow(static_cast<uint8_t>(*it)) } );
    return polyLoc;
}

gf::Poly rs::Encoder::calcPolyErr() const noexcept
{
    gf::Poly polyErr = polySyn * polyLoc;
    return std::vector<gf::Byte>(polyErr.cbegin(),
                                 polyErr.cbegin() + redundantCharCount
                                 );
}

gf::Poly rs::Encoder::calcMagnitudes(const gf::Poly &errPos) const
{
    gf::Poly magnitudes(
                std::vector<gf::Byte>(static_cast<uint8_t>(*(errPos.cend()-1)),0)
                );
    gf::Poly polyLocDer = polyLoc.der();
    std::for_each(errPos.cbegin(),errPos.cend(),
                  [this, &polyLocDer, &magnitudes](gf::Byte const& posErr)
    {
        gf::Byte x_inv = gf::Byte(1) / gf::Byte(2).pow(static_cast<uint8_t>(posErr));
        gf::Byte W = this->polyErr(x_inv);
        gf::Byte L = polyLocDer(x_inv);
        magnitudes[static_cast<uint8_t>(posErr)] = W / L;
    });
    return magnitudes;
}
