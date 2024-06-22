/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex06.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: June 22, 2024 [11:37 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Cross product");

    init_display(f32Vector a({0., 0., 1.}));
    init_display(f32Vector b({1., 0., 0.}));
    init_display(f32Vector c({1., 2., 3.}));
    init_display(f32Vector d({4., 5., 6.}));
    init_display(f32Vector e({4., 2., -3.}));
    init_display(f32Vector f({-2., -5., 16.}));
    init_display(f32Vector g({-4., -5., -6.}));

    assert_eq(cross_product(a, b) == f32Vector({0., 1., 0.}));
    assert_eq(cross_product(c, d) == f32Vector({-3., 6., -3.}));
    assert_eq(cross_product(d, c) == f32Vector({3., -6., 3.}));
    assert_eq(cross_product(e, f) == f32Vector({17., -58., -16.}));
    assert_eq(cross_product(a, a) == f32Vector({0., 0., 0.}));
    assert_eq(cross_product(d, g) == f32Vector({0., 0., 0.}));

    results();
}