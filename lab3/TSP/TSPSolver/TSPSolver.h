#pragma once

#include <list>
#include <utility>
#include <memory>
#include <cfloat>
#include <mutex>
#include <atomic>

#include "matrix.hpp"

class CMatrix;

class LittleSolver {
public:
    using Edges = std::list<std::pair<size_t, size_t>>;
    using MatrixPtr = std::unique_ptr<CMatrix>;

    LittleSolver(Matrix const& m);

    std::list<size_t> Solve();
    int GetRecord() const;

    LittleSolver(const LittleSolver&) = delete;
    LittleSolver& operator=(const LittleSolver&) = delete;

private:
    void HandleMatrix(const CMatrix& m, const Edges& arcs, int bottomLimit);
    int Cost(const Edges& path) const;
    void CandidateSolution(const Edges& arcs);
    void AddInfinity(CMatrix& m);
    int SubtractFromMatrix(CMatrix& m) const;
    std::list<std::pair<size_t, size_t>>  FindBestZeros(const CMatrix& matrix) const;
    static int GetPenalty(const CMatrix& m, size_t r, size_t c);

    MatrixPtr m_sourceMatrix;
    std::atomic<int> m_record = INF;
    Edges m_edges;
    std::list<size_t> m_solution;
    int m_removed = INF - 1;
};
