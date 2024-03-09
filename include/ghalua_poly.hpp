#ifndef __GHALUA_POLY_HPP_
#define __GHALUA_POLY_HPP_

#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>

#include "ghalua_byte.hpp"

namespace Gf
{



class Poly : public std::vector<Byte>
{
public:
    Poly();
    Poly(std::vector<Byte> const& p);
    Poly(Poly const& other);
    Poly(Byte const& num, size_t degree);
    ~Poly() = default;

    Poly operator + (Poly const& poly) const noexcept;
    void operator +=(Poly const& poly) noexcept;
    Poly operator * (Poly const& poly) const;
    Poly operator / (Poly const& divisor) const;

    friend std::ostream& operator << (std::ostream& stream, Poly const& _poly);
};//Poly



}//Gf

#endif//__GHALUA_POLY_HPP_
