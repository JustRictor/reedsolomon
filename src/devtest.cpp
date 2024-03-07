#include <iostream>
#include "ghalua_math.hpp"



int main()
{
    uint8_t a = 100;
    uint8_t b = 100;
    std::cout << (int)(a*b % 255);
    return 0;
}
