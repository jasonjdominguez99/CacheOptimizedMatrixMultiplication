#include "Matrix.h"

#include <iomanip>
#include <iostream>
#include <random>

Matrix::Matrix(const size_t numRows, const size_t numCols) :
    m_numRows(numRows),
    m_numCols(numCols),
    m_data(numRows * numCols)
{
    // Initialize with random values between 0.0 - 1.0
    std::random_device                    rd;
    std::mt19937                          gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (float& val : m_data)
    {
        val = dist(gen);
    }
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
