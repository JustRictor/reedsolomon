#ifndef __GHALUA_BYTE_HPP_
#define __GHALUA_BYTE_HPP_

#include <cstdint>
#include "ghalua_math.hpp"

namespace Gf
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
    Byte operator +  (Byte const& num) const noexcept;
    Byte operator -  (Byte const& num) = delete;
    Byte operator *  (Byte const& num) const noexcept;
    Byte operator /  (Byte const& num) const noexcept;

    Byte pow(uint8_t val) const noexcept;

private:
};//Byte



} //Gf

#endif//__GHALUA_BYTE_HPP_
