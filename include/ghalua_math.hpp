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
constexpr uint8_t indexMSB_(uint64_t const& num);

#if __GFPoly_ != 285
#warning Using a different polynomial may lead to unstable program behavior
#endif
/**
 * @brief Числовое представление порождающего полинома
 */
static const uint16_t polyGenerator_ = __GFPoly_;

/**
 * @brief Умножение двух чисел по правилам поля Галуа
 * @param num1 [in] первое число
 * @param num2 [in] второе число
 * @return результат умножения
 */
constexpr uint8_t mult(uint8_t const& num1, uint8_t const& num2);

/**
 * @brief Возведение числа в степень по правилам поля Галуа
 * @param num [in] число
 * @param n [in] степень
 * @return результат возведения в степень
 */
constexpr uint8_t pow(uint8_t const& num, uint8_t n);

/**
 * @brief Создание таблицы степеней двойки для поля Галуа 256
 * @return Сгенерированная таблица
 * \note Перенести в класс байта Галуа
 */
constexpr std::array<uint8_t, 256> genTable_();

}

#endif//__GHALUA_MATH_CPP_
