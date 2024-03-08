#include <iostream>
#include "ghalua_byte.hpp"
#include "ghalua_poly.hpp"



int main()
{
    Gf::Poly p1({8,9,2});
    Gf::Poly p2({6,11});
    Gf::Poly p3 = p1*p2;
    for(Gf::Byte const& b : p3)
    {
        std::cout << b << " ";
    }
    return 0;
}
