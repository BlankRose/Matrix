/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - ex12.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: June 25, 2024 [11:52 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    init_display(f32Matrix a({
        { 1, 2 },
        { 3, 4 }
    }));
    init_display(f32Matrix b({
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    }));
    init_display(f32Matrix c({
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    }));
    init_display(f32Matrix d({
        { 2, 0, 0 },
        { 0, 2, 0 },
        { 0, 0, 2 }
    }));
    init_display(f32Matrix e({
        { 8, 5, -2 },
        { 4, 7, 20 },
        { 7, 6, 1 }
    }));
    init_display(f32Matrix f({
        { 1, 4, 2, 1 },
        { 6, 8, 4, 3 },
        { 3, 4, 8, 6 },
        { 1, 2, 4, 1 }
    }));

    {
        title("Matrix Cofactor");

        assert_eq(a.cofactor() == f32Matrix({
            {  4, -3 },
            { -2,  1 }
        }));
        assert_eq(b.cofactor() == f32Matrix({
            { -3,   6, -3 },
            {  6, -12,  6 },
            { -3,   6, -3 }
        }));
        assert_eq(c.cofactor() == c);
        assert_eq(d.cofactor() == f32Matrix({
            { 4, 0, 0 },
            { 0, 4, 0 },
            { 0, 0, 4 }
        }));
        assert_eq(e.cofactor() == f32Matrix({
            { -113, 136, -25 },
            { -17, 22, -13 },
            { 114, -168, 36 }
        }));
        assert_eq(f.cofactor() == f32Matrix({
            { -96,  72, -18,  24 },
            {  48,  -6,  -6, -12 },
            { -12,  -6,  -6,  48 },
            {  24, -18,  72, -96 }
        }));

        results();
    }
    {
        title("Matrix Adjoint");

        assert_eq(a.adjoint() == f32Matrix({
            {  4, -2 },
            { -3,  1 }
        }));

        results();
    }
    {
        title("Matrix Inverse");

        assert_eq(a.inverse() == f32Matrix({
            { -2, 1 },
            { 1.5, -.5 }
        }));
        //std::cout << b.inverse() << std::endl; // NO INVERSE SINCE DET(b) = 0
        assert_eq(c.inverse() == f32Matrix({
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
        }));
        assert_eq(d.inverse() == f32Matrix({
            { .5, 0, 0 },
            { 0, .5, 0 },
            { 0, 0, .5 }
        }));
        //std::cout << e.inverse() << std::endl; // PRECISION ISSUES FOR TESTING...
        assert_eq(f.inverse() == f32Matrix({
            { -8./15, 4./15, -1./15, 2./15 },
            { 2./5, -1./30, -1./30, -1./10},
            { -1./10, -1./30, -1./30, 2./5},
            { 2./15, -1./15, 4./15, -8./15}
        }));

        results();
    }
}