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

gf::Poly rs::Encoder::encode(const gf::Poly &poly) noexcept
{
    return (poly >> redundantCharCount)
            + (poly >> redundantCharCount) / polyGenerators[redundantCharCount];
}
