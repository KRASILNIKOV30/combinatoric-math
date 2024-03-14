#pragma once

#include <vector>
#include <stdio.h>
#include "../TSPBruteForce/TSPBruteForce.h"

class Matrix 
{
public:
    explicit Matrix(Mat matrix);

    // доступ к элементам по индексам
    const int& item(size_t row, size_t column) const;
    int& item(size_t row, size_t column);
    const int& operator()(size_t row, size_t column) const;
    int& operator()(size_t row, size_t column);

    // получение "реальных" идексов
    // e.g. если была удалена строка 1 rowIndex(1) == 2
    // ?необходимо для алгоритма Литтла
    size_t rowIndex(size_t row) const;
    size_t columnIndex(size_t column) const;

    // размерность матрицы
    size_t size() const;
    // вывод на экран
    void print() const;
    void printEndl() const;

    // удаление строки и столбца по индексам
    void removeRowColumn(size_t row, size_t column);

    Matrix(const Matrix&) = default;
    Matrix& operator=(const Matrix&) = default;

private:
    // инициализация "реальных" номеров строк и столбцов
    void initRowsColumns();

    std::vector<std::vector<int>> _items;
    // "реальные" номера строк
    std::vector<size_t> _rows;
    // "реальные" номера столбцов
    std::vector<size_t> _columns;
};

inline Matrix::Matrix(Mat matrix)
    : _items(matrix)
    , _rows(matrix.size())
    , _columns(matrix.size())
{
    initRowsColumns();
}

inline const int& Matrix::item(size_t row, size_t column) const {
    return _items[row][column];
}

inline int& Matrix::item(size_t row, size_t column) {
    // по имя искоренения дублирования кода
    return const_cast<int&>(static_cast<const Matrix&>(*this).item(row, column));
}

inline const int& Matrix::operator()(size_t row, size_t column) const {
    return item(row, column);
}

inline int& Matrix::operator()(size_t row, size_t column) {
    return item(row, column);
}

inline size_t Matrix::rowIndex(size_t row) const {
    return _rows[row];
}

inline size_t Matrix::columnIndex(size_t column) const {
    return _columns[column];
}

inline void Matrix::removeRowColumn(size_t row, size_t column) {
    // удаление индексов
    _rows.erase(_rows.begin() + row);
    _columns.erase(_columns.begin() + column);
    // удаление строки
    _items.erase(_items.begin() + row);
    // удаление столбца
    for (size_t i = 0; i < _items.size(); i++)
        _items[i].erase(_items[i].begin() + column);
}

inline size_t Matrix::size() const {
    return _items.size();
}

inline void Matrix::print() const {
    printf("         ");
    for (auto iter = _columns.cbegin(); iter != _columns.cend(); ++iter)
        printf("%8u ", *iter);
    puts("");
    for (size_t i = 0; i < _items.size(); i++) {
        printf("%8u ", _rows[i]);
        for (size_t j = 0; j < _items.size(); j++) {
            printf("%8.2f ", _items[i][j]);
        }
        puts("");
    }
}

inline void Matrix::printEndl() const {
    print();
    puts("");
}

inline void Matrix::initRowsColumns() {
    for (size_t i = 0; i < _rows.size(); i++)
        _rows[i] = _columns[i] = i;
}
