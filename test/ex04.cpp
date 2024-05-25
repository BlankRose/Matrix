/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex04.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 25, 2024 [3:00 PM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Vector Norms");

    init_display(f32Vector a({0, 0, 0}));
    assert_eq(a.norm_1() == 0);
    assert_eq(a.norm_2() == 0);
    assert_eq(a.norm_inf() == 0);

    init_display(f32Vector b({1, 2, 3}));
    assert_eq(b.norm_1() == 6);
    assert_eq(round_n(b.norm_2(), 3) == 3.741);
    assert_eq(b.norm_inf() == 3);

    init_display(f32Vector c({-1, -2}));
    assert_eq(c.norm_1() == 3);
    assert_eq(round_n(c.norm_2(), 3) == 2.236);
    assert_eq(c.norm_inf() == 2);

    results();
}