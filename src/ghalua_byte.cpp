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

void Gf::Byte::operator +=(const Byte &num) noexcept
{
    value ^= num.value;
}

Gf::Byte Gf::Byte::pow(uint8_t num) const noexcept
{
    if(this->value == 0) return 0;
    if(num == 0) return 1;
    return pow2table[
            log2table[this->value] * num % 255
            ];
}

std::ostream & Gf::operator <<(std::ostream &stream, const Gf::Byte &byte)
{
    stream << std::setfill('0') << std::setw(2)
           << std::hex << std::uppercase
           << static_cast<int>(byte.value);
    return stream;
}
