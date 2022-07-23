#include <iostream>
#include "complex.hpp"

int main(void)
{
    Complex z1(1, 2);
    Complex z2(3, -4);
    Complex z3 = z2 + z1;
    Complex z4 = z2 - z1;
    Complex z5 = z2 * z1;
    Complex z6 = z1 / z2;
    bool b1 = z1 != z2;
    bool b2 = z1 == z2;

    std::cout << z1 << std::endl;
    std::cout << z2 << std::endl;
    std::cout << z3 << std::endl;
    std::cout << z4 << std::endl;
    std::cout << z5 << std::endl;
    std::cout << z6 << std::endl;
    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;

    return 0;
}