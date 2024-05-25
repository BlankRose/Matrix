/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex09.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 25, 2024 [2:19 PM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Matrix transpose");

    init_display(f32Matrix a({
        {1, 2, 3},
        {2, 1, 2},
        {3, 2, 1}
    }));
    init_display(f32Matrix b({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    }));
    init_display(f32Matrix c({
        {1, 2},
        {3, 4}
    }));
    init_display(f32Matrix d({
        {0, 3, 6, 9},
        {1, 2, 4, 8}
    }));

    assert_eq(a.transpose() == a);
    assert_eq(b.transpose() == f32Matrix({
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    }));
    assert_eq(c.transpose() == f32Matrix({
        {1, 3},
        {2, 4}
    }));
    assert_eq(d.transpose() == f32Matrix({
        {0, 1},
        {3, 2},
        {6, 4},
        {9, 8}
    }));
    assert_eq(b.transpose().transpose() == b);
    assert_eq(d.transpose().transpose() == d);

    results();
}