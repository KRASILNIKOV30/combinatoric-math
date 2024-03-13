#include <iostream>
#include <numeric>
#include "TSPBruteForce.h"
#include <algorithm>

int GetCost(Matrix const& matrix, std::vector<int> cycle)
{
    int result = 0;
    for (auto left = cycle.begin(), right = left + 1; right != cycle.end(); left++, right++)
    {
        result += matrix[*left][*right];
    }

    return result;
}

std::vector<int> GetEulerCycle(Matrix const& matrix)
{
    int minCost = INF;
    std::vector<int> result(matrix.size());
    std::iota(result.begin(), result.end(), 0);
    auto current = result;

    do
    {
        int cost = GetCost(matrix, current);
        if (cost < minCost)
        {
            minCost = cost;
            result = current;
        }
    } while (std::next_permutation(current.begin() + 1, current.end()));

    result.push_back(0);
    return result;
}
