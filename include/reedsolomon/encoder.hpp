#ifndef __ENCODER_HPP_
#define __ENCODER_HPP_

#include <unordered_map>
#include <iostream>

#include "reedsolomon/ghalua_poly.hpp"

namespace rs
{



class Encoder
{
protected:
    size_t const redundantCharCount;
    static inline std::unordered_map<size_t, gf::Poly> polyGenerators{};

    gf::Poly polySyn{};
    gf::Poly polyLoc{};
    gf::Poly polyErr{};
public:
    Encoder(size_t _redundantCharCount = 4);
    gf::Poly encode(gf::Poly const& poly) const;
    gf::Poly decode(gf::Poly const& poly);

protected:
    gf::Poly calcPolySyn(gf::Poly const& poly) const noexcept;
    gf::Poly calcErrPos() const;
    gf::Poly calcPolyLoc(gf::Poly const& errPos) const noexcept;
    gf::Poly calcPolyErr() const noexcept;
    gf::Poly calcMagnitudes(gf::Poly const& errPos) const;
};//Encoder



}//Rs

#endif//__ENCODER_HPP_
