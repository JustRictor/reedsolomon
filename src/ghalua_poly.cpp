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

Gf::Poly Gf::Poly::operator +(const Poly &poly) const noexcept
{
    Poly returnValue(*this);
    returnValue.resize(std::max(poly.size(),this->size()),0);
    std::transform(poly.cbegin(),poly.cend(),
                   returnValue.cbegin(),returnValue.begin(),
                   std::plus<>());
    return returnValue;
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

Gf::Poly Gf::Poly::operator /(const Poly &poly) const
{
    throw std::logic_error("not implemented");
}
