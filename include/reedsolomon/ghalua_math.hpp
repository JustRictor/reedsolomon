#ifndef __GHALUA_MATH_HPP_
#define __GHALUA_MATH_HPP_

#include <cstdint>
#include <string> //<size_t declaration
#include <array>

namespace Gf
{
/**
 * @brief Функция нахождения индекса старшего бита числа
 * @param num [in] число
 * @return Индекс искомого бита в числе
 */
constexpr uint8_t indexMSB_(uint64_t const& num)
{
    uint8_t itCount = 0;
    while( (num >> itCount) >= 1)
    {
        itCount++;
    }
    return itCount - 1;
}

#if __GFPoly_ != 285
#warning Using a different polynomial may lead to unstable program behavior
#endif
/**
 * @brief Числовое представление порождающего полинома
 */
static const uint16_t polyGenerator_ = __GFPoly_;
static constexpr uint8_t MSBpolyGen_ = indexMSB_(polyGenerator_);

/**
 * @brief Умножение двух чисел по правилам поля Галуа
 * @param num1 [in] первое число
 * @param num2 [in] второе число
 * @return результат умножения
 */
constexpr uint8_t mult(uint8_t const& num1, uint8_t const& num2)
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

/**
 * @brief Возведение числа в степень по правилам поля Галуа
 * @param num [in] число
 * @param n [in] степень
 * @return результат возведения в степень
 */
constexpr uint8_t pow(uint8_t const& num, uint8_t n)
{
    if(n == 0) return 1;
    if(n == 1) return num;
    uint8_t retValue = num;
    while(n-- > 1)
        retValue = Gf::mult(retValue,num);
    return retValue;
}

/**
 * @brief Создание таблицы степеней двойки для поля Галуа 256
 * @return Сгенерированная таблица
 * \note Перенести в класс байта Галуа
 */
constexpr std::array<uint8_t, 256> genPow2Table_()
{
    std::array<uint8_t, 256> table{1,2};
    for(size_t i = 2; i < 256; i++)
        table[i] = Gf::mult(table[i-1],2);
    return table;
}

constexpr std::array<uint8_t, 256> genLog2Table_()
{
    std::array<uint8_t, 256> pow2Table = genPow2Table_();
    std::array<uint8_t, 256> log2Table{};

    for(size_t i = 0; i < 256; i++)
        log2Table[pow2Table[i]] = i;

    return log2Table;
}

}

#endif//__GHALUA_MATH_CPP_
