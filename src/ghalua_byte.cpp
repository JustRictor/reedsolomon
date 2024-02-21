#include "ghalua_byte.hpp"

Gf::Byte::Byte()
    : value(0)
{}

Gf::Byte::Byte(Byte &&val)
    : value(val.value)
{}

Gf::Byte &Gf::Byte::operator=(const Byte &val)
{
    if(&val != this)
        value = val.value;
    return *this;
}

Gf::Byte::Byte(uint8_t val)
    : value(val)
{}

bool Gf::Byte::operator ==(const Byte &num) const noexcept
{ return value == num.value; }

Gf::Byte Gf::Byte::operator +(const Byte &num) const noexcept
{ return value ^ num.value;  }

/*!
 * 1011101 * 1011
 * 1011101 + 0 + 001011101 + 0001011101
 * 100
 *
 * 110 * 11
 * 110 + 1100
 * 1010
 * 1010 / 1011
 */
Gf::Byte Gf::Byte::operator *(const Byte &num) const
{
    Byte returnValue{0};
    uint8_t itCount = 0;
    /* Перемножение чисел с выходом за поле*/
    while(value != 0 || num.value != 0)
    {
        returnValue.value +=
                ( ( (value >> itCount) & 0x01 )
                  ^ ( (num.value >> itCount) & 0x01 ) ) << itCount;
        itCount++;
    }
    /**/
    return returnValue;
}

Gf::Byte Gf::Byte::operator /(const Byte &num) const
{
    Byte remainder{value};  //<Остаток от деления
    uint8_t divRes = 0;     //<Результат деления старших членов полиномов
    while(remainder.value > num.value)
    {
        divRes = 1 << (remainder.indexMSB() - num.indexMSB());
        remainder.value ^= num.value << divRes;
    }
}
