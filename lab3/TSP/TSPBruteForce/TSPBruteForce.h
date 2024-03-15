#pragma once
#include <vector>
#include <limits>

using Matrix = std::vector<std::vector<int>>;
constexpr int INF = std::numeric_limits<int>::max();

std::vector<int> GetEulerCycle(Matrix const& matrix);
int GetMinCost(Matrix const& matrix);