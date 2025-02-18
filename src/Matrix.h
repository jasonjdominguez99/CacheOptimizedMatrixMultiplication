#pragma once

#include <ostream>
#include <stddef.h>
#include <vector>

class Matrix
{
public:
    [[nodiscard]] static Matrix zeros(const size_t numRows, const size_t numCols);
    [[nodiscard]] static Matrix random(const size_t numRows, const size_t numCols, const float min, const float max);

    ~Matrix() = default;

    [[nodiscard]] size_t numRows() const noexcept { return m_numRows; };
    [[nodiscard]] size_t numCols() const noexcept { return m_numCols; };
    [[nodiscard]] float  valueAt(const size_t i, const size_t j) const { return m_data[i * m_numCols + j]; };

    [[nodiscard]] static Matrix multiply_naive(const Matrix& m1, const Matrix& m2);
    [[nodiscard]] static Matrix multiply_reordered(const Matrix& m1, const Matrix& m2);

    static void benchmark();

private:
    explicit Matrix(const size_t numRows, const size_t numCols) :
        m_numRows(numRows),
        m_numCols(numCols),
        m_data(numRows * numCols, 0.0f) {};

    std::vector<float>&       data() noexcept { return m_data; };
    const std::vector<float>& data() const noexcept { return m_data; };

private:
    std::vector<float> m_data;
    size_t             m_numRows;
    size_t             m_numCols;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);
