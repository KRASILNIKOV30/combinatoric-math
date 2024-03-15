#include <iostream>
#include <numeric>
#include "TSPBruteForce.h"
#include <algorithm>

int GetCost(Matrix const& matrix, std::vector<int> cycle)
{
    int result = 0;
    for (auto it = cycle.begin(); it + 1 != cycle.end(); it++)
    {
        int el = matrix[*it][*(it + 1)];
        if (el == INF)
        {
            return INF;
        }
        result += matrix[*it][*(it + 1)];
    }

    return result;
}

std::vector<int> GetEulerCycle(Matrix const& matrix)
{
    int minCost = INF;
    std::vector<int> result(matrix.size());
    std::iota(result.begin(), result.end(), 0);
    result.push_back(0);
    auto current = result;

    do
    {
        int cost = GetCost(matrix, current);
        if (cost < minCost)
        {
            minCost = cost;
            result = current;
        }
    } while (std::next_permutation(current.begin() + 1, current.end() - 1));

    return result;
}

int GetMinCost(Matrix const& matrix)
{
    int minCost = INF;
    std::vector<int> result(matrix.size());
    std::iota(result.begin(), result.end(), 0);
    result.push_back(0);
    auto current = result;

    do
    {
        int cost = GetCost(matrix, current);
        if (cost < minCost)
        {
            minCost = cost;
            result = current;
        }
    } while (std::next_permutation(current.begin() + 1, current.end() - 1));

    return GetCost(matrix, result);
}
