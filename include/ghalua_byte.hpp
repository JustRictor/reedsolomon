#ifndef __GHALUA_BYTE_HPP_
#define __GHALUA_BYTE_HPP_

#include <cstdint>

namespace Gf
{

/*!
 * 1011101 * 1011
 * 1011101 + 0 + 001011101 + 0001011101
 * 100
 *
 * 110 * 11
 * 110 + 1100
 * 1010
 */
class Byte
{
private:
    uint8_t value;
public:
    Byte() = default;
    Byte(Byte&& val) = default;
    Byte(Byte const& val) = default;
    Byte operator=(Byte const& val)
    { value = val.value; }
    ~Byte() = default;

    Byte(uint8_t val)
        : value(val)
    {}
    Byte operator=(Byte&& val)
    { value = val.value; }

    bool operator == (Byte const& num) const noexcept
    { return value == num.value; }
    Byte operator +  (Byte const& num) const noexcept
    { return value ^ num.value;  }
    Byte operator *  (Byte const& num) const
    {
        Byte returnValue{0};
        uint8_t itCount = 0;
        while(value != 0 || num.value != 0)
        {
            returnValue.value +=
                      ( ( (value >> itCount) & 0x01 )
                    ^ ( (num.value >> itCount) & 0x01 ) ) << itCount;
            itCount++;
        }
    }
    Byte operator /  (Byte const& num) const;

    Byte pow(uint8_t val) const;


};//Byte



} //Gf

#endif//__GHALUA_BYTE_HPP_
