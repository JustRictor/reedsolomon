#include "ghalua_math.hpp"

constexpr uint8_t Gf::indexMSB_(const uint64_t &num)
{
    uint8_t itCount = 0;
    while( (num >> itCount) >= 1)
    {
        itCount++;
    }
    return itCount - 1;
}

static constexpr uint8_t MSBpolyGen_ = Gf::indexMSB_(Gf::polyGenerator_);
constexpr uint8_t Gf::mult(const uint8_t &num1, const uint8_t &num2)
{
    if (num1 == 0 || num2 == 0) return 0;
    uint16_t returnValue = 0;
    uint8_t itCount = 0;
    /*Перемножение чисел с выходом за поле*/
    while( (num2 >> itCount) > 0 )
    {
        if( (num2 >> itCount) & 1 )
            returnValue ^= num1 << itCount;
        itCount++;
    }
    /*Деление на порождающий полином*/
    uint8_t MSBVal = indexMSB_(returnValue) % 16;
    while(MSBVal >= MSBpolyGen_)
    {
        uint16_t divRes = 1 << ( MSBVal - MSBpolyGen_ );
        returnValue ^= polyGenerator_ << indexMSB_(divRes);
        MSBVal = indexMSB_(returnValue);
    }
    return returnValue;
}

constexpr uint8_t Gf::pow(const uint8_t &num, uint8_t n)
{
    if(n == 0) return 1;
    if(n == 1) return num;
    uint8_t retValue = num;
    while(n-- > 1)
        retValue = Gf::mult(retValue,num);
    return retValue;
}

constexpr std::array<uint8_t, 256> Gf::genTable_()
{
    std::array<uint8_t, 256> table{1,2};
    for(size_t i = 2; i < 256; i++)
        table[i] = Gf::mult(table[i-1],2);
    return table;
}
