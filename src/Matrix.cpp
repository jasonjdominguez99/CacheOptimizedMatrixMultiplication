#include "Matrix.h"

#include <chrono>
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

Matrix Matrix::multiply_naive(const Matrix& m1, const Matrix& m2)
{
    if (m1.numCols() != m2.numRows())
    {
        throw std::runtime_error("Matrix sizes are not compatible for multiplication");
    }

    Matrix              result(m1.numRows(), m2.numCols());
    std::vector<float>& resultData = result.data();

    for (size_t i = 0; i < m1.numRows(); ++i)
    {
        for (size_t j = 0; j < m2.numCols(); ++j)
        {
            float sum = 0.0f;
            for (size_t k = 0; k < m1.numCols(); ++k)
            {
                sum += m1.valueAt(i, k) * m2.valueAt(k, j);
            }
            resultData[i * result.numCols() + j] = sum;
        }
    }

    return result;
}

Matrix Matrix::multiply_reordered(const Matrix& m1, const Matrix& m2)
{
    if (m1.numCols() != m2.numRows())
    {
        throw std::runtime_error("Matrix sizes are not compatible for multiplication");
    }

    Matrix              result(m1.numRows(), m2.numCols());
    std::vector<float>& resultData = result.data();

    for (size_t i = 0; i < m1.numRows(); ++i)
    {
        for (size_t k = 0; k < m1.numCols(); ++k)
        {
            const float value = m1.valueAt(i, k);
            for (size_t j = 0; j < m2.numCols(); ++j)
            {
                resultData[i * result.numCols() + j] += value * m2.valueAt(k, j);
            }
        }
    }

    return result;
}

void Matrix::benchmark()
{
    // Benchmark function to compare multiplication performance
    const size_t sizes[] = { 128, 256, 512, 1024, 2048 };

    float min = 0.0f;
    float max = 1.0f;

    for (size_t size : sizes)
    {
        std::cout << "Matrix size: " << size << "x" << size << "\n";

        Matrix a = Matrix::random(size, size, min, max);
        Matrix b = Matrix::random(size, size, min, max);

        auto   start = std::chrono::high_resolution_clock::now();
        Matrix naiveResult = multiply_naive(a, b);
        auto   end = std::chrono::high_resolution_clock::now();
        auto   naiveTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Naive multiplication time: " << naiveTime << "ms\n";

        start = std::chrono::high_resolution_clock::now();
        Matrix ReorderedResult = multiply_reordered(a, b);
        end = std::chrono::high_resolution_clock::now();
        auto reorderedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Reordered multiplication time: " << reorderedTime << "ms\n";
        std::cout << "Speedup: " << static_cast<float>(naiveTime) / reorderedTime << "x\n\n";
    }

    std::cout << std::endl;
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
