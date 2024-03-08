#include "ghalua_poly.hpp"

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
    throw std::logic_error("not implemented");
}

Gf::Poly Gf::Poly::operator /(const Poly &poly) const
{
    throw std::logic_error("not implemented");
}
