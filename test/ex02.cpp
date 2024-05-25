/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex02.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 25, 2024 [8:45 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    {
        title("Builtins linear interpolaton");

        assert_eq(lerp(0., 1., 0) == 0);
        assert_eq(lerp(0., 1., 1) == 1);
        assert_eq(lerp(0., 1., .5) == .5);
        assert_eq(round_n(lerp(21., 42., .3), 2) == 27.3);
        assert_eq(round_n(lerp(42., 21., .7), 2) == 27.3);

        results();
    }
    std::cout << std::endl;
    {
        title("User linear interpolation");

        init_display(f32Vector a({2, 1}));
        init_display(f32Vector b({4, 2}));

        assert_eq(lerp(a, b, .3) == f32Vector({2.6, 1.3}));
        assert_eq(lerp(b, a, .7) == f32Vector({2.6, 1.3}));

        init_display(f32Matrix c({
            {2, 1},
            {3, 4}
        }));
        init_display(f32Matrix d({
            {20, 10},
            {30, 40}
        }));

        assert_eq(lerp(c, d, .5) == f32Matrix({
            {11, 5.5},
            {16.5, 22}
        }));
        assert_eq(lerp(d, c, .5) == f32Matrix({
            {11, 5.5},
            {16.5, 22}
        }));

        results();
    }
}