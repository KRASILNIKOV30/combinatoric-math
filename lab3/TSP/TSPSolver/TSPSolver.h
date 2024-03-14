#pragma once

#include <list>
#include <utility>
#include <memory>
#include <cfloat>
#include <mutex>
#include <atomic>

#include "matrix.hpp"

class Matrix;

class LittleSolver {
public:
    // список вершин как список пар номеров смежных вершин
    using arclist = std::list<std::pair<size_t, size_t>>;
    using MatrixD = Matrix;
    using MatrixPtr = std::unique_ptr<Matrix>;

    // на вход матрица расстояний и требуемая верхняя граница
    LittleSolver(Matrix const& m);
    ~LittleSolver();

    // основной метод
    void solve();

    // получить решение
    std::list<size_t> getSolution() const;
    // получить послейдний шаг
    // [нужно только для визуализации]  
    arclist getLastStep() const;
    // получить лучшее промежуточное решение
    // [нужно только для визуализации]  
    arclist getBestStep() const;
    // получить рекорд
    int getRecord() const;
    // было ли найдето решение, не превышающее заданную границу
    bool isSolved() const;

    // не должен быть скопирован
    LittleSolver(const LittleSolver&) = delete;
    LittleSolver& operator=(const LittleSolver&) = delete;

private:
    // основная рекурсивная функция поиска пути
    // m - текущая матрица стоимостей
    // arcs - текущий найденный путь
    // bottomLimit - текущая нижняя граница
    void handleMatrix(const Matrix& m, const arclist& arcs, int bottomLimit);
    // скммарная длина набора ребер
    int cost(const arclist& arcs) const;
    // сравнить предложенное решение с оптимальным
    void candidateSolution(const arclist& arcs);
    // добавление недостающей бесконечности в матрицу
    // стоимостей для избежания преждевременных циклов
    void addInfinity(MatrixD& m);
    // произвести ряд вычитаний, чтобы в каждой строке
    // и каждом столбце были бесконечности.
    // возвращает значение, на которое увеличится нижняя граница
    int subtractFromMatrix(MatrixD& m) const;
    // поиск нулевых коэффициентов с максимальными коэффициентами
    std::list<std::pair<size_t, size_t>>  findBestZeros(const MatrixD& matrix) const;
    // получение коэффициента для элемента (r, c)
    // r - row; c - column
    static int getCoefficient(const MatrixD& m, size_t r, size_t c);
    // записать последний проверенный путь
    void logPath(const arclist& path);

    // исходная матрица расстояний
    MatrixPtr _sourceMatrix;
    // рекорд, он же длина лучшего пути, он же верхняя граница
    std::atomic<int> _record = INF;
    // лучшее решение
    arclist _arcs;
    // итоговое решение
    std::list<size_t> _solution;
    // последний просмотренный список ребер
    arclist _lastStep;
    // для доступа к промежуточным результатам из другого потока
    mutable std::mutex _mutex;
    // значение, принимаемое за бесконечность
    int _infinity;
};
