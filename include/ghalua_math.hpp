#ifndef __GHALUA_MATH_HPP_
#define __GHALUA_MATH_HPP_

#include <cstdint>

namespace Gf
{


template<typename T>
constexpr T indexMSB_(T num)
{
    T itCount = 0;
    while( (num >> itCount) >= 1 )
    {
        itCount++;
    }
    return itCount;
}

static const uint32_t polyGenerator_ = 11;
static constexpr uint32_t MSBpolyGen_ = indexMSB_(polyGenerator_);

template<typename T>
constexpr T mult(T const& num1, T const& num2)
{
    T returnValue = 0;
    uint8_t itCount = 0;
    /*Перемножение чисел с выходом за поле*/
    while( (num2 >> itCount) > 0 )
    {
        if( (num2 >> itCount) & 1 )
            returnValue ^= num1 << itCount;
        itCount++;
    }
    /*Деление на порождающий полином*/
    T MSBVal = indexMSB_(returnValue);
    while(MSBVal >= MSBpolyGen_)
    {
        MSBVal = indexMSB_(returnValue);
        T divRes = 1 << ( MSBVal - MSBpolyGen_ );
        returnValue ^= polyGenerator_ << (divRes - 1);
    }
    return returnValue;
}

template<typename T>
constexpr T pow(T const& num, T const& pow)
{
    if(pow <= 1)
        return num;
    return pow(mult(num,num),pow--);
}


}

#endif//__GHALUA_MATH_CPP_
