#include "../../../external/catch2/catch.hpp"
#include "../TSPBruteForce/TSPBruteForce.h"
#include "../TSPSolver/TSPSolver.h"
#include "../TSPSolver/Matrix.hpp"
#include "../../../external/core/core/Timer.h"
#include <algorithm>
#include <iterator>
#include <iostream>

constexpr bool TEST_WITH_TIMER_ENABLED = false;

namespace
{
	void Print(std::ranges::input_range auto&& r)
	{
		std::ranges::copy(r, std::ostream_iterator<int>(std::cout, " "));
	}
}

TEST_CASE("Brute force test")
{
	Mat mat = {
		{INF, 1, 0, 1, 1},
		{1, INF, 1, 1, 0},
		{1, 1, INF, 0, 1},
		{1, 0, 1, INF, 1},
		{0, 1, 1, 1, INF}
	};

	CHECK(GetEulerCycle(mat) == std::vector<int>{0, 2, 3, 1, 4, 0});
}

TEST_CASE("Test1")
{
	Mat mat = {
		{INF, 1, 0, 1, 1},
		{1, INF, 1, 1, 0},
		{1, 1, INF, 0, 1},
		{1, 0, 1, INF, 1},
		{0, 1, 1, 1, INF},
	};
	Matrix matrix(mat);
	LittleSolver solver(matrix);
	solver.solve();

	CHECK(std::ranges::equal(solver.getSolution(), GetEulerCycle(mat)));
}

TEST_CASE("Test2")
{
	Mat mat = {
		{2, 1},
		{1, 3},
	};
	Matrix matrix(mat);
	LittleSolver solver(matrix);
	solver.solve();

	CHECK(std::ranges::equal(solver.getSolution(), GetEulerCycle(mat)));
}

TEST_CASE("Test3")
{
	Mat mat = {
		{1, 2, 3, 4, 5},
		{1, 2, 3, 4, 5},
		{1, 2, 3, 4, 5},
		{1, 2, 3, 4, 5},
		{1, 2, 3, 4, 5},
	};
	Matrix matrix(mat);
	LittleSolver solver(matrix);
	solver.solve();

	CHECK(solver.getRecord() == GetMinCost(mat));
}

TEST_CASE("Test4")
{
	Mat mat = {
		{4, 2, 5, 4, 8},
		{1, 1, 10, 4, 0},
		{1, 8, 3, 4, 0},
		{5, 2, 6, 6, 3},
		{11, 2, 1, 4, 6},
	};
	Matrix matrix(mat);
	LittleSolver solver(matrix);
	solver.solve();

	CHECK(std::ranges::equal(solver.getSolution(), GetEulerCycle(mat)));
}

TEST_CASE("Test5")
{
	Mat mat = {
		{ INF, 5, 6, 9, 2, 5, 0 },
		{ 9, INF, 9, 2, 4, 6, 6 },
		{ 1, 9, INF, 4, 8, INF, 7 },
		{ 1, 5, 3, INF, 3, 8, 5 },
		{ 6, 5, 5, 6, INF, 2, 7 },
		{ 5, 3, 8, 7, 2, INF, 8 },
		{ 8, 7, 7, 4, 2, 1, INF },
	};
	Matrix matrix(mat);
	LittleSolver solver(matrix);
	solver.solve();

	CHECK(solver.getRecord() == GetMinCost(mat));
}

TEST_CASE_METHOD(TimerFixture, "Test with timer")
{
	if (!TEST_WITH_TIMER_ENABLED)
	{
		return;
	}

	Mat mat = {
		{ 8, 1, 7, 0, 3, 2, 2, 2, 4, 5, 5, 2, 0 },
		{ 1, 8, 5, 7, 1, 7, 7, 3, 4, 0, 8, 3, 0 },
		{ 7, 1, 2, 2, 8, 6, 8, 4, 6, 1, 8, 9, 3 },
		{ 3, 0, 3, 7, 9, 7, 7, 7, 7, 1, 9, 3, 9 },
		{ 2, 8, 2, 0, 1, 7, 6, 0, 8, 4, 4, 7, 7 },
		{ 1, 3, 8, 3, 7, 5, 6, 8, 4, 6, 2, 2, 9 },
		{ 9, 5, 3, 1, 5, 6, 5, 5, 9, 8, 4, 2, 0 },
		{ 6, 8, 7, 4, 8, 2, 8, 5, 2, 5, 3, 1, 3 },
		{ 4, 7, 6, 8, 5, 4, 6, 7, 4, 6, 0, 2, 5 },
		{ 3, 8, 2, 4, 8, 3, 1, 3, 7, 3, 1, 5, 2 },
		{ 0, 0, 7, 6, 2, 7, 3, 0, 5, 1, 0, 4, 0 },
		{ 0, 7, 2, 2, 6, 7, 2, 2, 3, 7, 8, 4, 4 },
		{ 0, 0, 2, 2, 1, 5, 8, 9, 2, 1, 7, 0, 2 },
	};
	Matrix matrix(mat);
	LittleSolver solver(matrix);

	StartTimer();
	solver.solve();
	double solverTime = StopTimer();

	StartTimer();
	auto minCost = GetMinCost(mat);
	double bruteForceTime = StopTimer();

	CHECK(solver.getRecord() == minCost);

	std::cout << "Matrix 13x13:" << std::endl;
	std::cout << "Brute force time: " << bruteForceTime << std::endl;
	std::cout << "Solver time: " << solverTime << std::endl;
}