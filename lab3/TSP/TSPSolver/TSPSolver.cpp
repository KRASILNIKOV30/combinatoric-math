#include "TSPSolver.h"
#include <iostream>
#include <numeric>

using std::list;
using std::vector;
using std::pair;
using std::mutex;
using std::lock_guard;

LittleSolver::LittleSolver(const Mat& m)
{
    m_sourceMatrix = std::make_unique<Matrix>(Matrix(m));
    m_infinity = INF - 1;
    for (size_t i = 0; i < m_sourceMatrix->size(); i++)
    {
        m_sourceMatrix->item(i, i) = INF - 1;
    }
}

std::list<size_t> LittleSolver::Solve()
{
    HandleMatrix(*m_sourceMatrix, Edges(), 0);
    m_solution.push_back(0);
    while (!m_edges.empty()) 
    {
        auto iter = m_edges.begin();
        while (iter != m_edges.end()) 
        {
            if (iter->first == m_solution.back()) 
            {
                m_solution.push_back(iter->second);
                iter = m_edges.erase(iter);
            }
            else
                ++iter;
        }
    }

    return m_solution;
}

int LittleSolver::GetRecord() const {
    return m_record;
}

void LittleSolver::HandleMatrix(const Matrix& m, const Edges& path, int bottomLimit) 
{
    auto size = m.size();
    if (size < 2)
    {
        throw std::logic_error("Matrix smaller than 2x2");
    }

    if (size == 2) 
    {
        int i = m.item(0, 0) >= m_infinity ? 1 : 0;
        Edges result(path);
        result.emplace_back(m.rowIndex(0), m.columnIndex(i));
        result.emplace_back(m.rowIndex(1), m.columnIndex(1 - i));
        CandidateSolution(result);
        return;
    }

    Matrix matrix(m);
    bottomLimit += SubtractFromMatrix(matrix);
    if (bottomLimit > m_record)
    {
        return;
    }

    auto zeros = FindBestZeros(matrix);
    if (!zeros.size())
    {
        return;
    }

    auto edge = zeros.front();
    auto newMatrix(matrix);
    newMatrix.removeRowColumn(edge.first, edge.second);
    auto newPath(path);
    newPath.emplace_back(matrix.rowIndex(edge.first), matrix.columnIndex(edge.second));
    AddInfinity(newMatrix);
    HandleMatrix(newMatrix, newPath, bottomLimit);

    newMatrix = matrix;
    newMatrix(edge.first, edge.second) = INF;
    HandleMatrix(newMatrix, path, bottomLimit);
}

int LittleSolver::Cost(const Edges& path) const 
{
    int result = 0;
    for (auto& iter : path)
    {
        auto el = m_sourceMatrix->item(iter.first, iter.second);
        if (el == INF || iter.first == iter.second)
        {
            return INF;
        }
        result += el;
    }

    return result;
}

void LittleSolver::CandidateSolution(const Edges& arcs) 
{
    int curCost;
    if (m_record <= (curCost = Cost(arcs))) {
        return;
    }
    m_record = curCost;
    m_edges = arcs;
}

void LittleSolver::AddInfinity(Matrix& m)
{
    vector<bool> infRow(m.size(), false);
    vector<bool> infColumn(m.size(), false);

    for (size_t i = 0; i < m.size(); i++)
    {
        for (size_t j = 0; j < m.size(); j++)
        {

            if (m.item(i, j) == m_infinity)
            {
                infRow[i] = true;
                infColumn[j] = true;
            }
        }
    }
        
    size_t notInf = 0;
    for (size_t i = 0; i < infRow.size(); i++)
    {
        if (!infRow[i])
        {
            notInf = i;
            break;
        }
    }
        
    for (size_t j = 0; j < infColumn.size(); j++)
    {
        if (!infColumn[j]) {
            m.item(notInf, j) = m_infinity;
            break;
        }
    }
}

int LittleSolver::SubtractFromMatrix(Matrix& m) const 
{
    vector<int> minRow(m.size(), INF);
    vector<int> minColumn(m.size(), INF);

    for (size_t i = 0; i < m.size(); ++i) 
    {
        for (size_t j = 0; j < m.size(); ++j)
        {
            if (m(i, j) < minRow[i])
            {
                minRow[i] = m(i, j);
            }
        }

        for (size_t j = 0; j < m.size(); ++j) 
        {
            if (m(i, j) < m_infinity) 
            {
                m(i, j) -= minRow[i];
            }
            if ((m(i, j) < minColumn[j]))
            {
                minColumn[j] = m(i, j);
            }
        }
    }

    for (size_t j = 0; j < m.size(); ++j)
    {
        for (size_t i = 0; i < m.size(); ++i)
        {
            if (m(i, j) < m_infinity)
            {
                m(i, j) -= minColumn[j];
            }
        }
    }
   
    return std::reduce(minColumn.begin(), minColumn.end(),
        std::reduce(minRow.begin(), minRow.end(), 0));
}

list<pair<size_t, size_t>> LittleSolver::FindBestZeros(const Matrix& matrix) const
{
    list<pair<size_t, size_t>> zeros;
    list<int> coeffList;

    int maxCoeff = 0;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            if (!matrix(i, j))
            {
                zeros.emplace_back(i, j);
                coeffList.push_back(GetPenalty(matrix, i, j));
                maxCoeff = std::max(maxCoeff, coeffList.back());
            }
        }
    }
       
    auto zIter = zeros.begin();
    auto cIter = coeffList.begin();
    while (zIter != zeros.end()) 
    {
        if (*cIter != maxCoeff)
        {
            zIter = zeros.erase(zIter);
            cIter = coeffList.erase(cIter);
        }
        else {
            ++zIter;
            ++cIter;
        }
    }

    return zeros;
}

int LittleSolver::GetPenalty(const Matrix& m, size_t r, size_t c)
{
    int rmin, cmin;
    rmin = cmin = INF;
    for (size_t i = 0; i < m.size(); ++i) 
    {
        if (i != r)
        {
            rmin = std::min(rmin, m(i, c));
        }
        if (i != c)
        {
            cmin = std::min(cmin, m(r, i));
        }
    }
    if (rmin > INF - cmin)
    {
        return INF;
    }
    return rmin + cmin;
}