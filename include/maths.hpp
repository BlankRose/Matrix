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

#include "general.hpp"
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
    { return maths::fma(v - u, t, u); }

template < class K >
K angle_cos(const Vector<K>& u, const Vector<K>& v)
{
    if (u.size() != v.size())
        throw std::logic_error("cannot operate on vectors of various sizes");
    if (!u.size())
        throw std::logic_error("cannot operate on zeroed vectors");
    return u.dot(v) / (u.norm_2() * v.norm_2());
}

template < class K >
Vector<K> cross_product(const Vector<K>& u, const Vector<K>& v)
{
    if (u.size() != 3 || v.size() != 3)
        throw std::logic_error("cannot operate on vectors with heights different than 3");
    return Vector<K>({
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
    });
}

#endif //MATHS_HPP