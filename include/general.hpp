/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - general.hpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: June 22, 2024 [8:56 AM]
//     ||  '-'
/* ************************************************************************** */

#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cmath>
#include <functional>

namespace maths
{
    // Adaptive FMA function, which takes the appropriate template
    // depending on if given T can use CPU-optimized FMA or not

    template < class X, class Y, class Z,
               typename = typename std::enable_if<std::is_fundamental<X>::value>::type,
               typename = typename std::enable_if<std::is_fundamental<Y>::value>::type,
               typename = typename std::enable_if<std::is_fundamental<Z>::value>::type >
    decltype(std::fma<X, Y, Z>) fma(const X& base, const Y& mul, const Z& add)
        { return std::fma(base, mul, add); }

    template < class X, class Y, class Z >
    auto fma(const X& base, const Y& mul, const Z& add) -> decltype(base * mul + add)
        { return base * mul + add; }

    template < class A, class B, class C, class D >
    auto cross_product(const A& a, const B& b, const C& c, const D& d) -> decltype(a * d - b * c)
        { return a * d - b * c; }

    template < class T, typename = typename
               std::enable_if<std::is_fundamental<T>::value>::type >
    T round_n(const T& value, const size_t& decimals)
    {
        double mul = 1.;
        for (size_t i = 0; i < decimals; ++i)
            mul *= 10.;
        return static_cast<T>(static_cast<int>(value * mul) / mul);
    }
}

#endif //GENERAL_HPP