#include "../../../external/catch2/catch.hpp"
#include "../Flow/Network.h"

SCENARIO("network tests")
{
	GIVEN("network")
	{
		Network network({
			{0, 25, 45, 30, 0, 0},
			{0, 0, 0, 0, 45, 0},
			{0, 10, 0, 0, 0, 15},
			{0, 0, 0, 0, 0, 35},
			{0, 0, 0, 0, 0, 25},
			{0, 0, 0, 0, 0, 0}
		});

		THEN("network initialized")
		{
			CHECK(network.GetFlow() == Matrix({
				{ 0, 25, 45, 30, 0, 0},
				{-25, 0, 0, 0, 0, 0 },
				{-45, 0, 0, 0, 0, 0 },
				{-30, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 }
			}));

			CHECK(network.GetLevels() == std::vector<int>{6, 0, 0, 0, 0, 0});
		}

		WHEN("push")
		{
			network.Push(2, 5);
			network.Push(2, 1);
			network.Push(1, 4);

			THEN("flow changed")
			{
				CHECK(network.GetFlow() == Matrix({
				{ 0, 25, 45, 30, 0, 0},
				{-25, 0, -10, 0, 35, 0 },
				{-45, 10, 0, 0, 0, 15 },
				{-30, 0, 0, 0, 0, 0 },
				{ 0, -35, 0, 0, 0, 0 },
				{ 0, 0, -15, 0, 0, 0 }
					}));

				CHECK(network.GetOverflow(0) == -100);
				CHECK(network.GetOverflow(1) == 0);
				CHECK(network.GetOverflow(2) == 20);
				CHECK(network.GetOverflow(3) == 30);
				CHECK(network.GetOverflow(4) == 35);
				CHECK(network.GetOverflow(5) == 15);
			}
		}

		WHEN("relabel")
		{
			network.Relabel(2);

			THEN("level changed")
			{
				CHECK(network.GetLevels()[2] == 1);
			}

			WHEN("relabel same vertex")
			{
				network.Relabel(2);

				THEN("level not changed")
				{
					CHECK(network.GetLevels()[2] == 1);
				}
			}
		}

		CHECK(network.GetMaxFlow() == 70);
		CHECK(network.GetFlow() == Matrix{ 
			{ 0, 15, 25, 30, 0, 0 }, 
			{ -15, 0, -10, 0, 25, 0 }, 
			{ -25, 10, 0, 0, 0, 15}, 
			{ -30, 0, 0, 0, 0, 30 },
			{ 0, -25, 0, 0, 0, 25 },
			{ 0, 0, -15, -30, -25, 0}
		});
	}
}

SCENARIO("network test")
{
	GIVEN("network")
	{
		Network network({
			{ 0, 0, 0, 25, 0, 45, 0, 0, 30, 0, 0 },
			{ 0, 0, 45, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25 },
			{ 0, 15, 0, 0, 35, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 35 },
			{ 0, 0, 0, 10, 20, 0, 15, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 25 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15 },
			{ 0, 0, 0, 0, 0, 0, 35, 0, 0, 45, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
		});

		THEN("can calculate max flow")
		{
			CHECK(network.GetMaxFlow() == 95);
		}
	}
}