/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex13.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: June 24, 2024 [2:17 PM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

// https://www.cuemath.com/algebra/rank-of-a-matrix/
// https://math.stackexchange.com/questions/21100/importance-of-matrix-rank

int main()
{
    title("Matrix Ranks");

    assert_eq(f32Matrix({
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    }).rank() == 3);
    assert_eq(f32Matrix({
        { 1, 2, 0, 0 },
        { 2, 4, 0, 0 },
        { -1, 2, 1, 1 }
    }).rank() == 2);
    assert_eq(f32Matrix({
        { 8, 5, -2 },
        { 4, 7, 20 },
        { 7, 6, 1 },
        { 21, 18, 7 }
    }).rank() == 3);
    assert_eq(f32Matrix({
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    }).rank() == 2);

    results();
}