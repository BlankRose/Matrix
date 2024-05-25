/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex03.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 25, 2024 [10:02 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Dot product");

    init_display(f32Vector a({0, 0}));
    init_display(f32Vector b({1, 1}));
    init_display(f32Vector c({-1, 6}));
    init_display(f32Vector d({3, 2}));

    assert_eq(a.dot(b) == 0);
    assert_eq(b.dot(b) == 2);
    assert_eq(c.dot(b) == 5);
    assert_eq(c.dot(d) == 9);
    assert_eq(d.dot(b) == 5);
    assert_eq(a.dot(c) == 0);

    results();
}