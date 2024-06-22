/* ************************************************************************** */
//         .-.
//   __   /   \   __
//  (  `'.\   /.'`  )  matrix-cpp - test_unit.hpp
//   '-._.(;;;)._.-'
//   .-'  ,`"`,  '-.
//  (__.-'/   \'-.__)  By: Rosie (https://github.com/BlankRose)
//      //\   /        Created at: May 25, 2024 [6:45 AM]
//     ||  '-'
/* ************************************************************************** */

#ifndef TEST_UNIT_HPP
#define TEST_UNIT_HPP

#include <iostream>

#define FLOAT_MARGIN 0.001

#define title(expr) \
    size_t total = 0; \
    size_t success = 0; \
    do { \
        std::cout << "\033[2;4m-- " expr " --\033[0m" << std::endl; \
    } while (false)

#define init_display(expr) \
    const expr; \
    do { \
        std::cout << "\033[1;33m"#expr"\033[0m" << std::endl; \
    } while (false)

#define assert_eq(expr) \
    do { \
        ++total; \
        if (!(expr)) \
            std::cout << "\033[1;31m[KO] Failure: \033[22m"#expr"\033[0m" << std::endl; \
        else \
        { \
            std::cout << "\033[1;32m[OK] Success: \033[22m"#expr"\033[0m" << std::endl; \
            ++success; \
        } \
    } while (false)

#define assert_feq(expr, expected) \
    do { \
        ++total; \
        auto res = expr; \
        if (res < expected - FLOAT_MARGIN || res > expected + FLOAT_MARGIN) \
            std::cout << "\033[1;31m[KO] Failure: \033[22m"#expr" == "#expected \
                         "\033[0;2m (Got: " << res << ")\033[0m" << std::endl; \
        else \
        { \
            std::cout << "\033[1;32m[OK] Success: \033[22m"#expr" == "#expected"\033[0m" << std::endl; \
            ++success; \
        } \
    } while (false)

#define results() \
    do { \
        std::cout << "\033[2m-- Results: " << success << " / " << total << " --\033[0m" << std::endl; \
    } while (false)

#endif //TEST_UNIT_HPP