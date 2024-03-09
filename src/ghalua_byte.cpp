#include "reedsolomon/ghalua_byte.hpp"

gf::Byte::Byte()
    : value(0)
{}

gf::Byte::Byte(uint8_t val)
    : value(val)
{}

bool gf::Byte::operator ==(const Byte &num) const noexcept
{ return value == num.value; }

bool gf::Byte::operator !=(const Byte &num) const noexcept
{ return value != num.value; }

gf::Byte gf::Byte::operator +(const Byte &num) const noexcept
{ return value ^ num.value;  }

void gf::Byte::operator +=(const Byte &num) noexcept
{
    value ^= num.value;
}

gf::Byte gf::Byte::operator *(const Byte &num) const noexcept
{
    if ( num.value   == 0 ) return 0;
    if ( this->value == 0 ) return 0;
    return pow2table[
            ( log2table[this->value] + log2table[num.value] ) % 255
            ];
}

gf::Byte gf::Byte::operator /(const Byte &num) const
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

gf::Byte gf::Byte::pow(uint8_t num) const noexcept
{
    if(this->value == 0) return 0;
    if(num == 0) return 1;
    return pow2table[
            log2table[this->value] * num % 255
            ];
}

std::ostream & gf::operator <<(std::ostream &stream, const Byte &_byte)
{
    stream << static_cast<int>(_byte.value);
    return stream;
}
