#include "../../../external/catch2/catch.hpp"
#include "../Gamma/PlanarEmbedder.h"
#include "../../../external/core/core/Timer.h"

SCENARIO("planar embedder tests")
{
	GIVEN("graph")
	{
		PlanarEmbedder embedder({
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

		WHEN("get planar graph")
		{
			auto planar = embedder.GetPlanarGraph();
			auto faces = planar.GetFaces();
			CHECK(planar.GetFaces().size() == 5);
			CHECK(std::ranges::equal(faces[0].GetVertexes(), std::initializer_list{ 6, 8, 1, 7 }));
			CHECK(std::ranges::equal(faces[1].GetVertexes(), std::initializer_list{ 4, 3, 2, 9, 5, 4, 12, 11, 10 }));
			CHECK(std::ranges::equal(faces[2].GetVertexes(), std::initializer_list{ 1, 2, 3, 4, 5, 6, 7 }));
			CHECK(std::ranges::equal(faces[3].GetVertexes(), std::initializer_list{ 2, 1, 8, 6, 5, 9 }));
			CHECK(std::ranges::equal(faces[4].GetVertexes(), std::initializer_list{ 4, 10, 11, 12 }));
		}
	}
}

SCENARIO("planar embedder negative tests")
{
	GIVEN("K5 graph")
	{
		PlanarEmbedder embedder({
			{1, 2},
			{2, 3},
			{3, 4},
			{4, 5},
			{5, 1},
			{2, 5},
			{1, 3},
			{1, 4},
			{2, 4},
			{3, 5},
		});

		THEN("graph is not planar")
		{
			CHECK_THROWS_AS(embedder.GetPlanarGraph(), std::runtime_error);
		}
	}

	GIVEN("K3,3 graph")
	{
		PlanarEmbedder embedder({
			{1, 4},
			{1, 5},
			{1, 6},
			{2, 4},
			{2, 5},
			{2, 6},
			{3, 4},
			{3, 5},
			{3, 6},
		});

		THEN("graph is not planar")
		{
			CHECK_THROWS_AS(embedder.GetPlanarGraph(), std::runtime_error);
		}
	}

	GIVEN("tree")
	{
		PlanarEmbedder embedder({
			{1, 2},
			{1, 3},
			{1, 4},
			{2, 5},
			{2, 6},
			{2, 7},
			{3, 8},
			{3, 9},
			{3, 10},
		});

		THEN("graph is not planar")
		{
			CHECK_THROWS_AS(embedder.GetPlanarGraph(), std::runtime_error);
		}
	}
}
