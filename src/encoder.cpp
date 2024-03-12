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
    gf::Poly syndromes(getSyndromes(poly));
    if( syndromes == gf::Poly( std::vector<gf::Byte>(redundantCharCount,0) ) )
        return poly << redundantCharCount;
    throw std::logic_error("not implemented");
}

gf::Poly rs::Encoder::getSyndromes(const gf::Poly &poly) const noexcept
{
    gf::Poly syndromes{};
    gf::Byte _x{2};
    for(size_t i = 0; i < redundantCharCount; i++)
        syndromes.push_back(poly(_x));
    return syndromes;
}
