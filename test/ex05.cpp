/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex05.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: June 22, 2024 [10:03 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Cosine");

    init_display(f32Vector a({1., 0.}));
    init_display(f32Vector b({0., 1.}));
    init_display(f32Vector c({-1., 1.}));
    init_display(f32Vector d({1., -1.}));
    init_display(f32Vector e({2., 1.}));
    init_display(f32Vector f({4., 2.}));
    init_display(f32Vector g({1., 2., 3.}));
    init_display(f32Vector h({4., 5., 6.}));
    init_display(f32Vector i({6., -4.}));
    init_display(f32Vector j({-2., 3}));

    assert_eq(angle_cos(a, a) == 1.);
    assert_eq(angle_cos(a, b) == 0.);
    assert_eq(angle_cos(c, d) == -1.);
    assert_eq(angle_cos(e, f) == 1.);
    assert_feq(angle_cos(g, h), 0.974632);
    assert_feq(angle_cos(i, j), -0.923077);

    results();
}