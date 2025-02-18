#include <iostream>

#include "Matrix.h"

int main()
{
    Matrix m1(3, 2);
    Matrix m2(2, 3);

    std::cout << "Matrix m1" << std::endl;
    std::cout << m1 << std::endl;

    std::cout << "Matrix m2" << std::endl;
    std::cout << m2 << std::endl;
}
