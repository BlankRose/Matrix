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
    const f32Matrix a(3, 2);
    std::cout << a << std::endl;

    const f32Matrix b({
        {2, 6},
        {6, 3},
        {7, 2}
    });
    std::cout << "0, 1 = " << b.at(0, 1) << std::endl;
    std::cout << b << std::endl;
}