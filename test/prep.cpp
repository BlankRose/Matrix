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
    const f32Matrix ma(3, 2);
    std::cout << ma << std::endl;

    const f32Matrix mb({
        {2, 6},
        {6, 3},
        {7, 2}
    });
    std::cout << "0, 1 = " << mb.at(0, 1) << std::endl;
    std::cout << mb << std::endl;

    const f32Vector va(3);
    std::cout << va << std::endl;

    const f32Vector vb({2, 6, 7});
    std::cout << "0, 1 = " << vb.at(1) << std::endl;
    std::cout << vb << std::endl;
}