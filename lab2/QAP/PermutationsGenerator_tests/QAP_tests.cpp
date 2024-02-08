#include "../../../external/catch2/catch.hpp"
#include "../QAP/GetMinAssignment.h"

TEST_CASE("Find min assignment for one element")
{
	CHECK(GetMinAssigment({ {1} }, { {1} }) == std::vector{1});
}

SCENARIO("Find min assignment for one element")
{
	GIVEN("Equal facilities and for both elements")
	{
		Matrix facilities = {
			{0, 1},
			{1, 0},
		};
		Matrix locations = {
			{0, 1},
			{2, 0},
		};

		THEN("Min assignment is the initial assignment")
		{
			CHECK(GetMinAssigment(facilities, locations) == std::vector{1, 2});
		}

		AND_GIVEN("Facility from 1 to 2 is less then 2 to 1")
		{
			facilities = {
				{0, 1},
				{2, 0},
			};

			THEN("The second element is at the first position")
			{
				CHECK(GetMinAssigment(facilities, locations) == std::vector{ 2, 1 });
			}
		}

		AND_GIVEN("Facility from 2 to 1 is less then 1 to 2")
		{
			facilities = {
				{0, 2},
				{1, 0},
			};

			THEN("The first element is at the first position")
			{
				CHECK(GetMinAssigment(facilities, locations) == std::vector{ 1, 2 });
			}
		}
	}
}

TEST_CASE("Find assignment for four elements")
{
	Matrix facilities = {
		{0, 2, 3, 1},
		{2, 0, 1, 4},
		{3, 1, 0, 2},
		{1, 4, 2, 0},
	};

	Matrix locations = {
		{0, 1, 2, 3},
		{1, 0, 4, 2},
		{2, 4, 0, 1},
		{3, 2, 1, 0},
	};

	CHECK(GetMinAssigment(facilities, locations) == std::vector{ 1, 3, 2, 4 });
}