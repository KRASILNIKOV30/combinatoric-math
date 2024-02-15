#include "../../../external/catch2/catch.hpp"
#include "../Backpack/FillBackpack.h"
#include "../../../external/core/core/Timer.h"
#include <iostream>

constexpr bool LOAD_TEST_ENABLED = true;

TEST_CASE("Fill Bacpack with one element")
{
	CHECK(FillBackpack(std::vector<int>{ 5 }, std::vector<int>{ 6 }, 10) == std::vector<int>{ 0 });
	CHECK(FillBackpack(std::vector<int>{ 11 }, std::vector<int>{ 6 }, 10).empty());
}

SCENARIO("Fill backpack tests")
{
	GIVEN("Weights and values")
	{
		std::vector<int> weights = { 1, 2, 3, 4, 5 };
		std::vector<int> values = { 5, 4, 3, 2, 1 };
		int maxWeight = 0;

		WHEN("Max weight is equal to zero")
		{
			maxWeight = 0;
			
			THEN("Backpack is empty")
			{
				CHECK(FillBackpack(weights, values, maxWeight).empty());
			}
		}

		WHEN("Max weight is equal to 5")
		{
			maxWeight = 5;

			THEN("The first and the second elements in backpack")
			{
				CHECK(FillBackpack(weights, values, maxWeight) == std::vector<int>{ 0, 1 });
			}
		}

		WHEN("Max weight is one less than weight of all elements")
		{
			maxWeight = 14;

			THEN("Only the most valueless element not in backpack")
			{
				CHECK(FillBackpack(weights, values, maxWeight) == std::vector<int>{ 0, 1, 2, 3 });
			}
		}

		WHEN("Max weight is equal to weight of all elements")
		{
			maxWeight = 15;

			THEN("All elements in backpack")
			{
				CHECK(FillBackpack(weights, values, maxWeight) == std::vector<int>{ 0, 1, 2, 3, 4 });
			}
		}

		WHEN("Max weight is greater than weight of all elements")
		{
			maxWeight = 16;

			THEN("All elements in backpack")
			{
				CHECK(FillBackpack(weights, values, maxWeight) == std::vector<int>{ 0, 1, 2, 3, 4 });
			}
		}
	}
}

TEST_CASE_METHOD(TimerFixture, "Load test")
{
	if (!LOAD_TEST_ENABLED)
	{
		return;
	}

	constexpr int ELEMENTS_NUMBER = 22;

	std::vector<int> weights(ELEMENTS_NUMBER);
	std::vector<int> values(ELEMENTS_NUMBER);
	int maxWeight = 10;

	StartTimer();
	CHECK(FillBackpack(weights, values, maxWeight).empty());
	std::cout << StopTimer() << std::endl;
}