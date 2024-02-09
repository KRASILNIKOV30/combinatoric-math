#pragma once
#include <vector>

using Matrix = std::vector<std::vector<int>>;

std::vector<int> GetMinAssigment(Matrix const& facilities, Matrix const& locations);
