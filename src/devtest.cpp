#include <iostream>
#include <iomanip>
#include "reedsolomon/ghalua_byte.hpp"
#include "reedsolomon/ghalua_poly.hpp"


int main()
{
    Gf::Poly p1({67,86,136,68});
    Gf::Poly p2({6,11,7});
    Gf::Poly p3 = p1/p2;
    std::cout << (p1 >> 2)     << "\n"
              << (p1 << 2)     << "\n"
              << (p1 << 4)     << "\n"
              << (p1 << 5)     << "\n";
    return 0;
}
