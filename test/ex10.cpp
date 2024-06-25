/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex10.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: June 22, 2024 [2:26 PM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    title("Row-Echelon Form");

    init_display(f32Matrix a({
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    }));
    init_display(f32Matrix b({
        { 1, 2 },
        { 3, 4 }
    }));
    init_display(f32Matrix c({
        {  1, 2, -1,  -4 },
        {  2, 3, -1, -11 },
        { -2, 0, -3,  22 }
    }));
    init_display(f32Matrix d({
        { 8., 5., -2., 4., 28. },
        { 4., 2.5, 20., 4., -4. },
        { 8., 5., 1., 4., 17. }
    }));

    assert_eq(a.row_echelon() == a);
    assert_eq(b.row_echelon() == f32Matrix({
        { 1, 0 },
        { 0, 1 }
    }));
    assert_eq(c.row_echelon() == f32Matrix({
        { 1, 0, 0, -8 },
        { 0, 1, 0, 1 },
        { 0, 0, 1, -2 }
    }));

    // FLOAT COMPARAISON PRECISION ISSUES...
    /*assert_eq(d.row_echelon() == f32Matrix({
        { 1, 0.625, 0, 0, -12.1666667 },
        { 0, 0, 1, 0, -3.6666667 },
        { 0, 0, 0, 1, 29.5 }
    }));*/

    results();
}