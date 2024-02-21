#include <iostream>
#include "ghalua_math.hpp"

void test_multiplication_GF8()
{
    static const uint8_t multTableGF8_valid[7][7] =
    {
        {1, 2, 3, 4, 5, 6, 7},
        {2, 4, 6, 3, 1, 7, 5},
        {3, 6, 5, 7, 4, 1, 2},
        {4, 3, 7, 6, 2, 5, 1},
        {5, 1, 4, 2, 7, 3, 6},
        {6, 7, 1, 5, 3, 2, 4},
        {7, 5, 2, 1, 6, 4, 3},
    };
    bool failFlag = false;
    std::cout << "\n" << __FUNCTION__ << ": START\n";
    for (uint8_t i = 0; i < 7; i++)
    {
        for (uint8_t j = 0; j < 7; j++)
        {
            uint8_t expectedValue = multTableGF8_valid[i][j];
            uint8_t testValue     = Gf::mult(i+1,j+1);
            if(expectedValue != testValue)
            {
                failFlag = true;
                std::cout << "\tFAIL ( " << (int)i+1 << " * " << (int)j+1 << " )"
                          << " = " << (int)testValue << " Expected: " << (int)expectedValue
                          << "\n";
            }
        }
    }
    std::cout << __FUNCTION__ << (failFlag ? ": FAIL" : ": PASS") << std::endl;
}

int main()
{
    test_multiplication_GF8();
    return 0;
}
