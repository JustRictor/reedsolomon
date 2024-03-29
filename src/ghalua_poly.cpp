#include "reedsolomon/ghalua_poly.hpp"

gf::Poly::Poly()
    : std::vector<Byte>()
{}

gf::Poly::Poly(const std::vector<Byte> &p)
    : std::vector<Byte>(p)
{}

gf::Poly::Poly(const Poly &other)
    : std::vector<Byte>(other)
{}

gf::Poly::Poly(const Byte &num, size_t degree)
    : std::vector<Byte>(degree + 1)
{
    (*this)[degree] = num;
}

gf::Poly& gf::Poly::operator=(const Poly &other)
{
    if(this == &other)
        return *this;
    this->clear();
    std::copy(other.cbegin(),other.cend(),std::back_inserter(*this));
    return *this;
}

gf::Poly gf::Poly::operator +(const Poly &poly) const noexcept
{
    Poly returnValue(*this);
    returnValue.resize(std::max(poly.size(),this->size()),0);
    std::transform(poly.cbegin(),poly.cend(),
                   returnValue.cbegin(),returnValue.begin(),
                   std::plus<>()
                   );
    return returnValue;
}

void gf::Poly::operator +=(const Poly &poly) noexcept
{
    this->resize(std::max(poly.size(),this->size()),0);
    std::transform(poly.cbegin(),poly.cend(),
                   this->cbegin(),this->begin(),
                   std::plus<>()
                   );
}

gf::Poly gf::Poly::operator *(const Poly &poly) const noexcept
{
    Poly returnValue{};
    returnValue.resize(this->size() + poly.size() - 1, 0);
    for(size_t i = 0; i < this->size(); i++)
    {
        for(size_t j = 0; j < poly.size(); j++)
        {
            returnValue[i+j] += (*this)[i] * poly[j];
        }
    }
    return returnValue;
}

void gf::Poly::operator *=(const Poly &poly) noexcept
{
    Poly result{};
    result.resize(this->size() + poly.size() - 1, 0);
    for(size_t i = 0; i < this->size(); i++)
    {
        for(size_t j = 0; j < poly.size(); j++)
        {
            result[i+j] += (*this)[i] * poly[j];
        }
    }
    (*this) = result;
}

gf::Poly gf::Poly::operator /(const Poly &divisor) const
{
    Poly dividend(*this);

    size_t (*findMajor)(Poly const& _poly) = [](Poly const& _poly)
    {
        for(auto it = _poly.cend() - 1; it != _poly.cbegin(); it--)
            if(*it != gf::Byte(0))
                return static_cast<size_t>(it - _poly.cbegin());
        return static_cast<size_t>(0);
    };

    size_t majorDividendIndex = findMajor(dividend);
    while(majorDividendIndex >= divisor.size() - 1)
    {
        Poly divResult(dividend[majorDividendIndex] / *(divisor.cend() - 1),
                       majorDividendIndex - (divisor.size() - 1)
                    );
        dividend += divisor * divResult;

        majorDividendIndex = findMajor(dividend);
    }

    for(auto it = dividend.end() - 1; it != dividend.begin(); it--)
        if(*it == 0) dividend.erase(it);
        else break;

    return dividend;
}

gf::Byte gf::Poly::operator()(const Byte &x) const noexcept
{//\todo add tests
    size_t xPow = 0;
    return std::accumulate(this->cbegin(),this->cend(), Byte(0),
                           [&x,&xPow](Byte const& sum, Byte const& val)
    {
        return sum + val * x.pow(xPow++);
    });
}

gf::Poly gf::Poly::der() const noexcept
{//\todo add tests
    Poly returnValue(*this << 1);
    for(size_t i = 1; i < returnValue.size(); i += 2)
        returnValue[i] = 0;
    return returnValue;
}

gf::Poly gf::Poly::operator >>(size_t shiftCount) const noexcept
{
    if(shiftCount == 0)
        return *this;
    Poly returnValue(*this);
    if( static_cast<size_t>(-1) - shiftCount < returnValue.size() )
        returnValue.erase(returnValue.cend() - (returnValue.size() + shiftCount),
                          returnValue.cend()
                          );
    returnValue.insert(returnValue.cbegin(),shiftCount,0);
    return returnValue;
}

void gf::Poly::operator >>=(size_t shiftCount) noexcept
{
    if(shiftCount == 0)
        return;
    if( static_cast<size_t>(-1) - shiftCount < this->size() )
        this->erase(this->cend() - (this->size() + shiftCount),
                    this->cend()
                    );
    this->insert(this->cbegin(), shiftCount, 0);
}

gf::Poly gf::Poly::operator <<(size_t shiftCount) const noexcept
{
    if(shiftCount == 0)
        return *this;
    if(shiftCount > this->size())
        return Poly(std::vector<Byte>{});
    Poly returnValue(*this);
    returnValue.erase(returnValue.cbegin(), returnValue.cbegin() + shiftCount);
    return returnValue;
}

void gf::Poly::operator <<=(size_t shiftCount) noexcept
{
    if(shiftCount == 0)
        return;
    if(shiftCount > this->size())
        this->erase(this->cbegin());
    this->erase(this->cbegin(),this->cbegin() + shiftCount);
}

std::ostream &gf::operator <<(std::ostream &stream, const Poly &_poly)
{
    std::copy(_poly.cbegin(),_poly.cend(),
              std::ostream_iterator<gf::Byte>(std::cout," ")
              );
    return stream;
}
