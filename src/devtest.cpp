#include <iostream>
#include <iomanip>
#include "ghalua_byte.hpp"
#include "ghalua_poly.hpp"


int main()
{
    Gf::Poly p1({67,86,136,68});
    Gf::Poly p2({6,11,7});
    Gf::Poly p3 = p1/p2;
    std::cout << p3;
    return 0;
}
