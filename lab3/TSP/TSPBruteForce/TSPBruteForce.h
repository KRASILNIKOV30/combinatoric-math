#pragma once
#include <vector>
#include <limits>

using Mat = std::vector<std::vector<int>>;
constexpr int INF = std::numeric_limits<int>::max();

std::vector<int> GetEulerCycle(Mat const& matrix);
int GetMinCost(Mat const& matrix);