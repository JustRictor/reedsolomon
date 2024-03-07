#include "ghalua_byte.hpp"

Gf::Byte::Byte()
    : value(0)
{}

Gf::Byte::Byte(uint8_t val)
    : value(val)
{}

bool Gf::Byte::operator ==(const Byte &num) const noexcept
{ return value == num.value; }

Gf::Byte Gf::Byte::operator +(const Byte &num) const noexcept
{ return value ^ num.value;  }

Gf::Byte Gf::Byte::operator *(const Byte &num) const noexcept
{
    return pow2table[
            ( log2table[this->value] + log2table[num.value] ) % 255
            ];
}

Gf::Byte Gf::Byte::operator /(const Byte &num) const
{
    if(this->value == 0) return 0;
    if(num.value == 0) throw std::invalid_argument("division by 0");
    return pow2table[
            ( log2table[this->value] - log2table[num.value] ) % 255
            ];
}

Gf::Byte Gf::Byte::pow(uint8_t num) const noexcept
{
    if(this->value == 0) return 0;
    if(num == 0) return 1;
    return pow2table[
            log2table[this->value] * num % 255
            ];
}
