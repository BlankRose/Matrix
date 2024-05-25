/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - maths.hpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 24, 2024 [11:16 AM]
//     ||  '-'
/* ************************************************************************** */

#ifndef MATHS_HPP
#define MATHS_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

template < class K >
Vector<K> linear_combination(const std::vector<Vector<K>>& u, const std::vector<K>& coefs)
{
    if (u.size() != coefs.size())
        throw std::logic_error("cannot operate on arrays of different lengths");
    if (u.empty())
        return Vector<K>(0);

    size_t scale = u[0].size();
    Vector<K> tmp(scale);
    for (size_t i = 0; i < u.size(); ++i)
    {
        if (u[i].size() != scale)
            throw std::logic_error("cannot operate on vectors of various sizes");
        tmp += u[i] * coefs[i];
    }
    return tmp;
}

template < class V >
V lerp(const V& u, const V& v, const float& t)
{
    V dist = v - u;
    V aprox = dist * t;
    return u + aprox;
}

template < class V >
V round_n(const V& value, const size_t& decimals)
{
    double mult = 1.;
    for (size_t i = 0; i < decimals; ++i)
        mult *= 10.;
    return static_cast<V>(static_cast<int>(value * mult) / mult);
}

// u = 0, v = 1, t
// dist = v - u = 1 - 0 = 1
// aprox = 1t
// u + 1t

// t = 0 --> 0 + (1 * 0)  = 0 + 0  = 0
// t = 1 --> 0 + (1 * 1)  = 0 + 1  = 1
// t = .5 -> 0 + (1 * .5) = 0 + .5 = .5

#endif //MATHS_HPP