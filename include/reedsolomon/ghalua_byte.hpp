#ifndef __GHALUA_BYTE_HPP_
#define __GHALUA_BYTE_HPP_

#include <cstdint>
#include <stdexcept>
#include <iostream>

#include "reedsolomon/ghalua_math.hpp"

namespace gf
{


class Byte
{
private:
    uint8_t value;
    static constexpr auto pow2table = genPow2Table_();
    static constexpr auto log2table = genLog2Table_();

public:
    Byte();
    Byte(uint8_t val);

    bool operator == (Byte const& num) const noexcept;
    bool operator != (Byte const& num) const noexcept;

    Byte operator +  (Byte const& num) const noexcept;
    Byte operator *  (Byte const& num) const noexcept;
    Byte operator /  (Byte const& num) const;

    void operator += (Byte const& num) noexcept;

    Byte pow(uint8_t num) const noexcept;

    friend std::ostream& operator << (std::ostream& stream, Byte const& _byte);

private:
};//Byte



} //Gf

#endif//__GHALUA_BYTE_HPP_
