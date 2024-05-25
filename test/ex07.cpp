/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex07.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 25, 2024 [11:59 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

/// Reference:
/// https://matrix.reshish.com/multCalculation.php

int main()
{
    {
        title("Matrix-Vector multiplication");

        init_display(f32Vector a({4, 2}));
        init_display(f32Matrix b({
            {1, 0},
            {0, 1}
        }));
        init_display(f32Matrix c({
            {2, 0},
            {0, 2}
        }));
        init_display(f32Matrix d({
            {2, -2},
            {-2, 2}
        }));

        assert_eq(b * a == f32Vector({4, 2}));
        assert_eq(c * a == f32Vector({8, 4}));
        assert_eq(d * a == f32Vector({4, -4}));

        results();
    }
    std::cout << std::endl;
    {
        title("Matrix-Matrix multiplication");

        init_display(f32Matrix a({
            {1, 0},
            {0, 1}
        }));
        init_display(f32Matrix b({
            {2, 1},
            {4, 2}
        }));
        init_display(f32Matrix c({
            {3, -5},
            {6, 8}
        }));
        init_display(f32Matrix d({
            {4, 1, 6, .5},
            {8, 3, 20, 100}
        }));
        init_display(f32Matrix e({
            {3, 2},
            {2, 6},
            {6, 2},
            {2, 3}
        }));

        assert_eq(a * a == a);
        assert_eq(a * b == b);
        assert_eq(c * b == f32Matrix({
            {-14, -7},
            {44, 22}
        }));
        assert_eq(c * d == f32Matrix({
            {-28, -12, -82, -498.5},
            {88, 30, 196, 803}
        }));
        assert_eq(e * d == f32Matrix({
            { 28, 9, 58, 201.5},
            { 56, 20, 132, 601},
            { 40, 12, 76, 203},
            { 32, 11, 72, 301}
        }));
        assert_eq(d * e == f32Matrix({
            {51, 27.5},
            {350, 374}
        }));

        results();
    }
}