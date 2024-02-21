#ifndef __GHALUA_BYTE_HPP_
#define __GHALUA_BYTE_HPP_

#include <cstdint>

namespace Gf
{


static const uint16_t polyGenerator_ = 285;

class Byte
{
private:
    uint8_t value;
public:
    Byte();
    Byte(Byte&& val);;
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
    uint8_t indexMSB() const noexcept
    {
        uint8_t ind = value;
        ind |= ind >> 1;
        ind |= ind >> 2;
        ind |= ind >> 4;
        return ind - (ind >> 1);
    }
};//Byte



} //Gf

#endif//__GHALUA_BYTE_HPP_
