#pragma once

#include <ostream>
#include <stddef.h>
#include <vector>

class Matrix
{
public:
    explicit Matrix(const size_t numRows, const size_t numCols);
    ~Matrix() = default;

    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;
    Matrix(Matrix&&) = delete;
    Matrix& operator=(Matrix&&) = delete;

    [[nodiscard]] size_t numRows() const noexcept { return m_numRows; };
    [[nodiscard]] size_t numCols() const noexcept { return m_numCols; };
    [[nodiscard]] float  valueAt(const size_t i, const size_t j) const { return m_data[i * m_numCols + j]; };

private:
    std::vector<float> m_data;
    size_t             m_numRows;
    size_t             m_numCols;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);
