/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex01.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 25, 2024 [7:46 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Linear combination");

    init_display(f32Vector e1({1, 0, 0}));
    init_display(f32Vector e2({0, 1, 0}));
    init_display(f32Vector e3({0, 0, 1}));
    init_display(f32Vector v1({1, 2, 3}));
    init_display(f32Vector v2({0, 10, -100}));

    assert_eq(linear_combination<float>({e1, e2, e3}, {10, -2, .5}) == f32Vector({10, -2, .5}));
    assert_eq(linear_combination<float>({v1, v2}, {10, -2}) == f32Vector({10, 0, 230}));

    results();
}