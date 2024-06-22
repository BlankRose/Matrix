/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex08.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: June 22, 2024 [12:05 PM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Matrix Trace");

    init_display(f32Matrix a({
        {1, 0},
        {0, 1}
    }));
    init_display(f32Matrix b({
        {2, -5, 0},
        {4, 3, 7},
        {-2, 3, 4}
    }));
    init_display(f32Matrix c({
        {-2, -8, 4},
        {1, -23, 4},
        {0, 6, 4}
    }));

    assert_eq(a.trace() == 2);
    assert_eq(b.trace() == 9);
    assert_eq(c.trace() == -21);

    results();
}