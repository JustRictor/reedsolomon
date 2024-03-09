#ifndef __ENCODER_HPP_
#define __ENCODER_HPP_

#include <unordered_map>
#include <iostream>

#include "reedsolomon/ghalua_poly.hpp"

namespace rs
{



class Encoder
{
private:
    size_t const redundantCharCount;
    std::unordered_map<size_t, gf::Poly> polyGenerators;

public:
    Encoder(size_t _redundantCharCount = 4);
    gf::Poly encode(gf::Poly const& poly) noexcept;
};//Encoder



}//Rs

#endif//__ENCODER_HPP_
