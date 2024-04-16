#include "../../../external/catch2/catch.hpp"
#include "../Gamma/Graph.h"

SCENARIO("graph tests")
{
	GIVEN("graph")
	{
		Graph graph({
			{1, 2},
			{2, 9},
			{9, 5},
			{5, 6},
			{6, 7},
			{7, 1},
			{6, 8},
			{8, 1},
			{2, 3},
			{3, 4},
			{4, 5},
			{4, 10},
			{10, 11},
			{11, 12},
			{12, 4},
		});

		WHEN("pop first cycle")
		{
			auto cycle = graph.PopFirstCycle();
			CHECK(std::ranges::equal(cycle, std::initializer_list{ 1, 2, 3, 4, 5, 6, 8 }));

			THEN("Segment was deleted from graph")
			{
				auto vertexes = graph.GetVertexes();
				for (auto& [v, _] : vertexes)
				{
					if (v == 3 || v == 8)
					{
						CHECK_FALSE(vertexes.contains(v));
					}
					else
					{
						CHECK(vertexes.contains(v));
					}

					if (v == 1 || v == 6 || v == 2 || v == 5 || v == 4)
					{
						CHECK(vertexes.at(v).IsContact());
					}
					else
					{
						CHECK_FALSE(vertexes.at(v).IsContact());
					}
				} 
				CHECK(vertexes.at(4).GetEdges().size() == 2);
				CHECK(vertexes.at(9).GetEdges().size() == 2);
				CHECK(vertexes.at(6).GetEdges().size() == 1);
				CHECK(vertexes.at(1).GetEdges().size() == 1);
				CHECK(vertexes.at(7).GetEdges().size() == 2);
				CHECK(vertexes.at(5).GetEdges().size() == 1);
				CHECK(vertexes.at(2).GetEdges().size() == 1);
			}

			AND_WHEN("get segments")
			{
				auto segments = graph.GetSegments();
				CHECK(segments.size() == 5);
			}
		}

	}

	GIVEN("K4 graph")
	{
		Graph graph({
			{1, 2},
			{2, 3},
			{3, 4},
			{4, 1},
			{1, 3},
			{2, 4},
		});

		WHEN("pop first cycle")
		{
			auto cycle = graph.PopFirstCycle();
			CHECK(std::ranges::equal(cycle, std::initializer_list{ 1, 2, 3, 4 }));

			THEN("nothing was deleted")
			{
				CHECK(graph.GetVertexes().size() == 4);
			}

			WHEN("get segments")
			{
				auto segments = graph.GetSegments();
				
				THEN("graph has two segments")
				{
					CHECK(segments.size() == 4);
					CHECK(std::ranges::equal(segments[0], std::initializer_list{ 1, 3 }));
					CHECK(std::ranges::equal(segments[1], std::initializer_list{ 2, 4 }));
				}
			}
		}

	}
}