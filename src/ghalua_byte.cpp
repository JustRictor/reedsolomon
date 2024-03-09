#include "reedsolomon/ghalua_byte.hpp"

Gf::Byte::Byte()
    : value(0)
{}

Gf::Byte::Byte(uint8_t val)
    : value(val)
{}

bool Gf::Byte::operator ==(const Byte &num) const noexcept
{ return value == num.value; }

bool Gf::Byte::operator !=(const Byte &num) const noexcept
{ return value != num.value; }

Gf::Byte Gf::Byte::operator +(const Byte &num) const noexcept
{ return value ^ num.value;  }

void Gf::Byte::operator +=(const Byte &num) noexcept
{
    value ^= num.value;
}

Gf::Byte Gf::Byte::operator *(const Byte &num) const noexcept
{
    if ( num.value   == 0 ) return 0;
    if ( this->value == 0 ) return 0;
    return pow2table[
            ( log2table[this->value] + log2table[num.value] ) % 255
            ];
}

Gf::Byte Gf::Byte::operator /(const Byte &num) const
{
    if ( this->value == 0 ) return 0;
    if ( num.value   == 0 ) throw std::invalid_argument("division by 0");

    ///\note определенно есть более правильное решение
    if (log2table[this->value] > log2table[num.value])
        return pow2table[
                static_cast<uint8_t>( log2table[this->value] - log2table[num.value] )
                ];
    else
        return pow2table[
                static_cast<uint8_t>( log2table[this->value] - log2table[num.value] ) - 1
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

std::ostream & Gf::operator <<(std::ostream &stream, const Byte &_byte)
{
    stream << static_cast<int>(_byte.value);
    return stream;
}
