#include "../../../external/catch2/catch.hpp"
#include "../TSPBruteForce/TSPBruteForce.h"

TEST_CASE("Brute force test")
{
	Matrix matrix = {
		{INF, 1, 0, 1, 1},
		{1, INF, 1, 1, 0},
		{1, 1, INF, 0, 1},
		{1, 0, 1, INF, 1},
		{0, 1, 1, 1, INF}
	};

	CHECK(GetEulerCycle(matrix) == std::vector<int>{0, 2, 3, 1, 4, 0});
}