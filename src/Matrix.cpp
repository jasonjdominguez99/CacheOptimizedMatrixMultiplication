#include "Matrix.h"

#include <iomanip>
#include <iostream>
#include <random>

Matrix Matrix::zeros(const size_t numRows, const size_t numCols)
{
    return Matrix(numRows, numCols);
}

Matrix Matrix::random(const size_t numRows, const size_t numCols, const float min, const float max)
{
    Matrix m(numRows, numCols);

    // Initialize with random values between min & max
    std::random_device                    rd;
    std::mt19937                          gen(rd());
    std::uniform_real_distribution<float> dist(min, max);

    std::vector<float>& data = m.data();
    for (float& val : data)
    {
        val = dist(gen);
    }

    return m;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    os << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < matrix.numRows(); ++i)
    {
        os << "[";

        for (size_t j = 0; j < matrix.numCols(); ++j)
        {
            os << std::setw(8) << matrix.valueAt(i, j);

            if (j < matrix.numCols() - 1)
            {
                os << ", ";
            }
        }

        os << " ]\n";
    }

    return os;
}
