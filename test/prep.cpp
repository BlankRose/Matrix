/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - prep.cpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 24, 2024 [10:59 AM]
//     ||  '-'
/* ************************************************************************** */

#include "common.hpp"

int main()
{
    {
        title("Matrix structure");

        init_display(f32Matrix a(3, 2));
        init_display(f32Matrix b({
            {2, 6},
            {6, 3},
            {7, 2}
        }));

        std::cout << "Matrix A:\n" << a << std::endl;
        std::cout << "Matrix B:\n" << b << std::endl;

        assert_eq(a.shape() == std::make_pair(3ul, 2ul));
        assert_eq(b.shape() == std::make_pair(3ul, 2ul));
        assert_eq(a.at(0, 0) == 0);
        assert_eq(b.at(0, 0) == 2);
        assert_eq(b.at(0, 1) == 6);
        assert_eq(b.at(1, 0) == 6);
        assert_eq(b.at(1, 1) == 3);
        assert_eq(b.at(2, 0) == 7);
        assert_eq(b.at(2, 1) == 2);
        assert_eq((b[{2, 0}] == 7));
        assert_eq(b.has(1, 1) == true);
        assert_eq(b.has(3, 0) == false);
        assert_eq(b.has(0, 2) == false);

        results();
    }
    std::cout << std::endl;
    {
        title("Vector structure");

        init_display(f32Vector a(3));
        init_display(f32Vector b({2, 6, 7, 8}));
        init_display(f32Matrix c({ {2}, {6}, {7}, {8} }));

        std::cout << "Vector A:\n" << a << std::endl;
        std::cout << "Vector B:\n" << b << std::endl;

        assert_eq(a.shape() == std::make_pair(3ul, 1ul));
        assert_eq(b.shape() == std::make_pair(4ul, 1ul));
        assert_eq(a.at(0) == 0);
        assert_eq(b.at(0) == 2);
        assert_eq(b.at(1) == 6);
        assert_eq(b.at(2) == 7);
        assert_eq(b.at(3) == 8);
        assert_eq(b[2] == 7);
        assert_eq(b.has(2) == true);
        assert_eq(b.has(4) == false);
        assert_eq(b.to_matrix() == c);
        assert_eq(b == c.to_vector());
        assert_eq(b == c);

        results();
    }
}