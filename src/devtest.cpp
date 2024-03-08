#include <iostream>
#include "ghalua_byte.hpp"
#include "ghalua_poly.hpp"



int main()
{
    Gf::Poly p1({3,8,11,7});
    Gf::Poly p2({19,0,6});
    Gf::Poly p3 = p1+p2;
    for(Gf::Byte const& b : p3)
    {
        std::cout << b << " ";
    }
    return 0;
}
