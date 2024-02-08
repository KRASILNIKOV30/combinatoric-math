#include "../../../external/catch2/catch.hpp"
#include "../QAP/PermutationsGenerator.h"
#include <algorithm>
#include <iostream>

SCENARIO("Permutations generator tests")
{
	GIVEN("Permutations generator for single element")
	{
		PermutationsGenerator generator(1);

		WHEN("Get first permutation")
		{
			CHECK(generator.IsNextAvailable());
			CHECK(generator.GetNext() == std::vector<int>{1});

			THEN("Next permutation is not available")
			{
				CHECK_FALSE(generator.IsNextAvailable());
			}
		}
	}

	GIVEN("Permutation generator for two elements")
	{
		PermutationsGenerator generator(2);

		WHEN("Can get two permutations")
		{
			CHECK(generator.GetNext() == std::vector<int>{ 1, 2 });
			CHECK(generator.GetNext() == std::vector<int>{ 2, 1 });

			THEN("Next permutation is not available")
			{
				CHECK_FALSE(generator.IsNextAvailable());
			}
		}
	}

	GIVEN("Permutation generator for five elements")
	{
		PermutationsGenerator generator(5);

		THEN("Elements in the first permutations are sorted")
		{
			CHECK(std::ranges::is_sorted(generator.GetNext()));
		}

		THEN("Amount of permutations is equal to 5!")
		{
			int count = 0;
			std::vector<int> lastPerm;
			while (generator.IsNextAvailable())
			{	
				lastPerm = generator.GetNext();
				++count;
			}
			CHECK(count == 120);
		}
	}
}