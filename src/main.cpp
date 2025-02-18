#include <iostream>

#include "Matrix.h"

int main()
{
    float min = 0.0f;
    float max = 1.0f;

    Matrix m1 = Matrix::random(3, 2, min, max);
    Matrix m2 = Matrix::random(2, 3, min, max);

    std::cout << "Matrix m1" << std::endl;
    std::cout << m1 << std::endl;

    std::cout << "Matrix m2" << std::endl;
    std::cout << m2 << std::endl;
}
