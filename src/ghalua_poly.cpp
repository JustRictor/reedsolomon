#include "ghalua_poly.hpp"

Gf::Poly::Poly()
    : std::vector<Byte>()
{}

Gf::Poly::Poly(const std::vector<Byte> &p)
    : std::vector<Byte>(p)
{}

Gf::Poly::Poly(const Poly &other)
    : std::vector<Byte>(other)
{}

Gf::Poly::Poly(const Byte &num, size_t degree)
    : std::vector<Byte>(degree + 1)
{
    (*this)[degree] = num;
}

Gf::Poly Gf::Poly::operator +(const Poly &poly) const noexcept
{
    Poly returnValue(*this);
    returnValue.resize(std::max(poly.size(),this->size()),0);
    std::transform(poly.cbegin(),poly.cend(),
                   returnValue.cbegin(),returnValue.begin(),
                   std::plus<>()
                   );
    return returnValue;
}

void Gf::Poly::operator +=(const Poly &poly) noexcept
{
    this->resize(std::max(poly.size(),this->size()),0);
    std::transform(poly.cbegin(),poly.cend(),
                   this->cbegin(),this->begin(),
                   std::plus<>()
                   );
}

Gf::Poly Gf::Poly::operator *(const Poly &poly) const
{
    Poly returnValue{};
    returnValue.resize(this->size() + poly.size() - 1, 0);
    for(size_t i = 0; i < this->size(); i++)
    {
        for(size_t j = 0; j < poly.size(); j++)
        {
            returnValue[i+j] += (*this)[i] * poly[j];
        }
    }
    return returnValue;
}

Gf::Poly Gf::Poly::operator /(const Poly &divisor) const
{
    Poly dividend(*this);

    size_t (*findMajor)(Poly const& _poly) = [](Poly const& _poly)
    {
        for(auto it = _poly.cend() - 1; it != _poly.cbegin(); it--)
            if(*it != 0)
                return static_cast<size_t>(it - _poly.cbegin());
        return static_cast<size_t>(0);
    };

    size_t majorDividendIndex = findMajor(dividend);
    while(majorDividendIndex >= divisor.size() - 1)
    {
        Poly divResult(dividend[majorDividendIndex] / *(divisor.cend() - 1),
                       majorDividendIndex - (divisor.size() - 1)
                    );
        dividend += divisor * divResult;

        majorDividendIndex = findMajor(dividend);
    }
    return dividend;
}

std::ostream &Gf::operator <<(std::ostream &stream, const Poly &_poly)
{
    std::copy(_poly.cbegin(),_poly.cend(),
              std::ostream_iterator<Gf::Byte>(std::cout," ")
              );
    return stream;
}
