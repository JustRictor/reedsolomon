#ifndef __GHALUA_POLY_HPP_
#define __GHALUA_POLY_HPP_

#include <vector>
#include <algorithm>
#include <numeric>

#include "ghalua_byte.hpp"

namespace Gf
{



class Poly : public std::vector<Byte>
{
public:
    Poly(std::vector<Byte> const& p);
    Poly(Poly const& other);
    ~Poly() = default;

    Poly operator + (Poly const& poly) const noexcept;
    Poly operator * (Poly const& poly) const;
    Poly operator / (Poly const& poly) const;

};//Poly



}//Gf

#endif//__GHALUA_POLY_HPP_
