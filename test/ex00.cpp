/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex00.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 25, 2024 [5:59 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    {
        title("Vector operations");

        init_display(f32Vector a({2, 3}));
        init_display(f32Vector b({5, 7}));

        assert_eq(a + b == f32Vector({7, 10}));
        assert_eq(a - b == f32Vector({-3, -4}));
        assert_eq(a * 2 == f32Vector({4, 6}));
        assert_eq(b * .5 == f32Vector({2.5, 3.5}));

        results();
    }
    std::cout << std::endl;
    {
        title("Matrix operations");

        init_display(f32Matrix a({
            {1, 2},
            {3, 4}
        }));
        init_display(f32Matrix b({
            {7, 4},
            {-2, 2}
        }));

        assert_eq(a + b == f32Matrix({
            {8, 6},
            {1, 6}
        }));
        assert_eq(a - b == f32Matrix({
            {-6, -2},
            {5, 2}
        }));
        assert_eq(a * 2 == f32Matrix({
            {2, 4},
            {6, 8}
        }));
        assert_eq(b * .5 == f32Matrix({
            {3.5, 2},
            {-1, 1}
        }));

        results();
    }
}