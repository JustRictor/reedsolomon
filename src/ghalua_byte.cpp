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
    //\todo fixme
    return 0;
}

Gf::Byte Gf::Byte::operator /(const Byte &num) const noexcept
{
    //\todo fixme
    return 0;
}
