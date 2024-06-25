/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex11.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: June 24, 2024 [3:54 PM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Matrix Determinant");

    assert_eq(f32Matrix(0, 0)
        .determinant() == 1);
    assert_eq(f32Matrix({
        { 6 }
    }).determinant() == 6);
    assert_eq(f32Matrix({
        { .5 }
    }).determinant() == .5);
    assert_eq(f32Matrix({
        { 1, -1 },
        { -1, 1 }
    }).determinant() == 0);
    assert_eq(f32Matrix({
        { 1, 2 },
        { 3, 4 }
    }).determinant() == -2);
    assert_eq(f32Matrix({
        { 2, 0, 0 },
        { 0, 2, 0 },
        { 0, 0, 2 }
    }).determinant() == 8);
    assert_eq(f32Matrix({
        { 8, 5, -2 },
        { 4, 7, 20 },
        { 7, 6, 1 }
    }).determinant() == -174);
    assert_eq(f32Matrix({
        { 8, 5, -2, 4 },
        { 4, 2.5, 20, 4 },
        { 8, 5, 1, 4 },
        { 28, -4, 17, 1 }
    }).determinant() == 1032);
    assert_eq(f32Matrix({
        {  1,  2,  3,  4 },
        {  5,  6,  7,  8 },
        {  9, 10, 11, 12 },
        { 13, 14, 15, 16 }
    }).determinant() == 0);
    assert_eq(f32Matrix({
        {  3, 16,  3,  5, 12 },
        { 35, 36, 10,  8,  4 },
        {  4,  1, 12,  7,  9 },
        { 45, 31, 12, 10,  0 },
        {  1,  6, 70,  3,  4 }
    }).determinant() == -164601);

    results();
}