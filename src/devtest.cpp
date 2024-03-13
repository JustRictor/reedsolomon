#include <iostream>
#include <iomanip>
#include "reedsolomon/ghalua_byte.hpp"
#include "reedsolomon/ghalua_poly.hpp"
#include "reedsolomon/encoder.hpp"

struct DisplayInHex
{
    gf::Poly poly;
    DisplayInHex(gf::Poly const& _poly)
        : poly(_poly)
    {}
    friend std::ostream& operator << (std::ostream& stream, DisplayInHex const& _disp)
    {
        std::for_each(_disp.poly.cbegin(),_disp.poly.cend(),
                      [&stream](gf::Byte const& byte)
        {
            stream << std::setfill('0') << std::setw(2)
                   << std::hex << std::uppercase
                   << byte << " ";
        });
        return stream;
    }
};

int main()
{
    gf::Poly poly({0x01, 0x2D, 0xA5, 0xC6, 0x8C, 0xDF});
    rs::Encoder encoder;
    std::cout << DisplayInHex{poly.der()};
    return 0;
}
