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
    // ������ ������ ��� ������ ��� ������� ������� ������
    using arclist = std::list<std::pair<size_t, size_t>>;
    using MatrixD = Matrix;
    using MatrixPtr = std::unique_ptr<Matrix>;

    // �� ���� ������� ���������� � ��������� ������� �������
    LittleSolver(Matrix const& m);
    ~LittleSolver();

    // �������� �����
    void solve();

    // �������� �������
    std::list<size_t> getSolution() const;
    // �������� ���������� ���
    // [����� ������ ��� ������������]  
    arclist getLastStep() const;
    // �������� ������ ������������� �������
    // [����� ������ ��� ������������]  
    arclist getBestStep() const;
    // �������� ������
    int getRecord() const;
    // ���� �� ������� �������, �� ����������� �������� �������
    bool isSolved() const;

    // �� ������ ���� ����������
    LittleSolver(const LittleSolver&) = delete;
    LittleSolver& operator=(const LittleSolver&) = delete;

private:
    // �������� ����������� ������� ������ ����
    // m - ������� ������� ����������
    // arcs - ������� ��������� ����
    // bottomLimit - ������� ������ �������
    void handleMatrix(const Matrix& m, const arclist& arcs, int bottomLimit);
    // ��������� ����� ������ �����
    int cost(const arclist& arcs) const;
    // �������� ������������ ������� � �����������
    void candidateSolution(const arclist& arcs);
    // ���������� ����������� ������������� � �������
    // ���������� ��� ��������� ��������������� ������
    void addInfinity(MatrixD& m);
    // ���������� ��� ���������, ����� � ������ ������
    // � ������ ������� ���� �������������.
    // ���������� ��������, �� ������� ���������� ������ �������
    int subtractFromMatrix(MatrixD& m) const;
    // ����� ������� ������������� � ������������� ��������������
    std::list<std::pair<size_t, size_t>>  findBestZeros(const MatrixD& matrix) const;
    // ��������� ������������ ��� �������� (r, c)
    // r - row; c - column
    static int getCoefficient(const MatrixD& m, size_t r, size_t c);
    // �������� ��������� ����������� ����
    void logPath(const arclist& path);

    // �������� ������� ����������
    MatrixPtr _sourceMatrix;
    // ������, �� �� ����� ������� ����, �� �� ������� �������
    std::atomic<int> _record = INF;
    // ������ �������
    arclist _arcs;
    // �������� �������
    std::list<size_t> _solution;
    // ��������� ������������� ������ �����
    arclist _lastStep;
    // ��� ������� � ������������� ����������� �� ������� ������
    mutable std::mutex _mutex;
    // ��������, ����������� �� �������������
    int _infinity;
};
