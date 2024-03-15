#pragma once

#include <vector>
#include <stdio.h>
#include <numeric>
#include "../TSPBruteForce/TSPBruteForce.h"

class CMatrix 
{
public:
    explicit CMatrix(Matrix matrix);
    const int& Item(size_t row, size_t column) const;
    int& Item(size_t row, size_t column);
    const int& operator()(size_t row, size_t column) const;
    int& operator()(size_t row, size_t column);
    size_t RowIndex(size_t row) const;
    size_t ColumnIndex(size_t column) const;
    size_t Size() const;
    void RemoveRowColumn(size_t row, size_t column);
    CMatrix(const CMatrix&) = default;
    CMatrix& operator=(const CMatrix&) = default;

private:
    void InitRowsColumns();

private:
    Matrix m_items;
    std::vector<size_t> m_rows;
    std::vector<size_t> m_columns;
};

inline CMatrix::CMatrix(Matrix matrix)
    : m_items(matrix)
    , m_rows(matrix.size())
    , m_columns(matrix.size())
{
    InitRowsColumns();
}

inline const int& CMatrix::Item(size_t row, size_t column) const {
    return m_items[row][column];
}

inline int& CMatrix::Item(size_t row, size_t column) {
    return const_cast<int&>(static_cast<const CMatrix&>(*this).Item(row, column));
}

inline const int& CMatrix::operator()(size_t row, size_t column) const {
    return Item(row, column);
}

inline int& CMatrix::operator()(size_t row, size_t column) {
    return Item(row, column);
}

inline size_t CMatrix::RowIndex(size_t row) const {
    return m_rows[row];
}

inline size_t CMatrix::ColumnIndex(size_t column) const {
    return m_columns[column];
}

inline void CMatrix::RemoveRowColumn(size_t row, size_t column) {
    m_rows.erase(m_rows.begin() + row);
    m_columns.erase(m_columns.begin() + column);
    m_items.erase(m_items.begin() + row);
    for (size_t i = 0; i < m_items.size(); i++)
    {
        m_items[i].erase(m_items[i].begin() + column);
    }
}

inline size_t CMatrix::Size() const {
    return m_items.size();
}

inline void CMatrix::InitRowsColumns() {
    std::iota(m_rows.begin(), m_rows.end(), 0);
    std::iota(m_columns.begin(), m_columns.end(), 0);
}
