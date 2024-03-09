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
    gf::Poly poly({0x44, 0x4F, 0x4E, 0x27, 0x54, 0x20, 0x50, 0x41, 0x4E, 0x49, 0x43});
    rs::Encoder encoder;
    std::cout << DisplayInHex{encoder.encode(poly)};
    return 0;
}
