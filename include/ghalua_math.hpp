#ifndef __GHALUA_MATH_HPP_
#define __GHALUA_MATH_HPP_

#include <cstdint>
#include <string> //<size_t declaration
#include <array>

namespace Gf
{

template<typename T>
constexpr uint8_t indexMSB_(T const& num)
{
    uint8_t itCount = 0;
    while( (num >> itCount) >= 1)
    {
        itCount++;
    }
    return itCount - 1;
}

static const uint16_t polyGenerator_ = 285;
static constexpr uint8_t MSBpolyGen_ = indexMSB_(polyGenerator_);

constexpr uint8_t mult(uint8_t const& num1, uint8_t const& num2)
{
    if (num1 == 0 || num2 == 0) return 0;
    uint64_t returnValue = 0; //<\64 чтобы при любом значении не улететь за старший бит
    uint8_t itCount = 0;
    /*Перемножение чисел с выходом за поле*/
    while( (num2 >> itCount) > 0 )
    {
        if( (num2 >> itCount) & 1 )
            returnValue ^= num1 << itCount;
        itCount++;
    }
    /*Деление на порождающий полином*/
    uint8_t MSBVal = indexMSB_(returnValue);
    while(MSBVal >= MSBpolyGen_)
    {
        uint8_t divRes = 1 << ( MSBVal - MSBpolyGen_ );
        returnValue ^= polyGenerator_ << (divRes - 1);
        MSBVal = indexMSB_(returnValue);
    }
    return returnValue;
}

constexpr uint8_t pow(uint8_t const& num, uint8_t n)
{
    if(n == 0) return 1;
    if(n == 1) return num;
    uint8_t retValue = num;
    while(n-- > 1)
        retValue = Gf::mult(retValue,num);
    return retValue;
}


constexpr std::array<uint8_t, 256> genTable_()
{
    std::array<uint8_t, 256> table{1,2};
    for(size_t i = 2; i < 256; i++)
        table[i] = Gf::mult(table[i-1],2);
    return table;
}

static constexpr std::array<uint8_t,256> tablePow = genTable_();

}

#endif//__GHALUA_MATH_CPP_
