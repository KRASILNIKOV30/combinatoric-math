#include "../../../external/catch2/catch.hpp"
#include "../HungarianAlgorithm/Distributor.h"
#include <iostream>

SCENARIO("distributor tests")
{
	GIVEN("simple graph")
	{
		Distributor distr({
			{ 0, 7, 9 },
			{ 1, 8, 3 },
			{ 10, 12, 15 }
		});

		THEN("matrix initialized")
		{
			CHECK(distr.GetMatrix() == Matrix({
				{ INF, 0, 0 },
				{ 0, 7, 0 },
				{ 0, 2, 3 },
			}));
		}
	}
}

SCENARIO("tests")
{
	GIVEN("matrix")
	{
		Distributor distr({
			{ 50, 0, 0, 10, 0, 20, 0 },
			{ 0, 30, 45, 0, 30, 0, 25 },
			{ 0, 5, 0, 0, 10, 15, 0 },
			{ 15, 0, 0, 20, 0, 0, 0 },
			{ 0, 0, 20, 0, 0, 5, 0 },
			{ 0, 0, 0, 0, 40, 0, 5 },
			{ 0, 0, 0, 15, 0, 0, 0 }
		});

		THEN("matrix initialized")
		{
			CHECK(distr.GetMatrix() == Matrix({
				{ 40, INF, INF, 0, INF, 10, INF },
				{ INF, 5, 5, INF, 0, INF, 0 },
				{ INF, 0, INF, INF, 0, 10, INF },
				{ 0, INF, INF, 5, INF, INF, INF },
				{ INF, INF, 0, INF, INF, 0, INF },
				{ INF, INF, INF, INF, 30, INF, 0 },
				{ INF, INF, INF, 0, INF, INF, INF }
			}));
		}

		CHECK(distr.GetMinMatch() == Match({
			{0, 5},
			{1, 4},
			{2, 1},
			{3, 0},
			{4, 2},
			{5, 6},
			{6, 3}
		}));

		CHECK(distr.GetSubsets() == Subsets({ { 0, 6 }, { 3 } }));

		CHECK(distr.GetMatrix() == Matrix({
			{ 30, INF, INF, 0, INF, 0, INF },
			{ INF, 5, 5, INF, 0, INF, 0 },
			{ INF, 0, INF, INF, 0, 10, INF },
			{ 0, INF, INF, 15, INF, INF, INF },
			{ INF, INF, 0, INF, INF, 0, INF },
			{ INF, INF, INF, INF, 30, INF, 0 },
			{ INF, INF, INF, 0, INF, INF, INF }
		}));
	}
}

SCENARIO("matrix without full match")
{
	GIVEN("matrix")
	{
		Distributor distr({
			{ 8, 0, 5, 0 },
			{ 0, 6, 0, 0 },
			{ 0, 7, 0, 0 },
			{ 0, 0, 3, 1 }
		});

		THEN("full match does not exist")
		{
			CHECK_THROWS_WITH(distr.GetMinMatch(), "full match does not exist");
		}
	}
}

SCENARIO("full graph")
{
	GIVEN("full graph")
	{
		Distributor distr({
			{ 5, 7, 9 },
			{ 1, 2, 3 },
			{ 15, 12, 10 },
		});

		THEN("can find min match")
		{
			CHECK(distr.GetMinMatch() == Match({
				{ 0, 0 },
				{ 1, 1 },
				{ 2, 2 }
			}));
		}
	}
}