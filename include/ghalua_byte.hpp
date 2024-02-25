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

public:
    Byte();
    Byte(Byte&& val);
    Byte(Byte const& val) = default;
    Byte& operator=(Byte const& val);
    ~Byte() = default;

    Byte(uint8_t val);

    bool operator == (Byte const& num) const noexcept;
    Byte operator +  (Byte const& num) const noexcept;
    Byte operator *  (Byte const& num) const;
    Byte operator /  (Byte const& num) const;

    Byte pow(uint8_t val) const;

private:
};//Byte



} //Gf

#endif//__GHALUA_BYTE_HPP_
