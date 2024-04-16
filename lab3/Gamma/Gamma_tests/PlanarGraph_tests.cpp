#include "../../../external/catch2/catch.hpp"
#include "../Gamma/PlanarGraph.h"
#include "../../../external/core/core/Timer.h"
#include <iostream>

SCENARIO("planar graph tests")
{
	GIVEN("planar graph (./Res/planar.png)")
	{
		PlanarGraph planar({ 1, 2, 3, 4, 5, 6, 7 });
		planar.AddSegment({ 1, 8, 6 });
		planar.AddSegment({ 2, 9, 5 });
		planar.AddSegment({ 4, 10, 11, 12, 4 });

		THEN("planar graph was correctly built")
		{
			auto faces = planar.GetFaces();
			REQUIRE(faces.size() == 5);
			auto it = faces.begin();

			CHECK(std::ranges::equal(it++->GetVertexes(), std::initializer_list{ 6, 7, 1, 8 }));
			CHECK(std::ranges::equal(it++->GetVertexes(), std::initializer_list{ 4, 3, 2, 9, 5, 4, 12, 11, 10 }));
			CHECK(std::ranges::equal(it++->GetVertexes(), std::initializer_list{ 1, 2, 3, 4, 5, 6, 8 }));
			CHECK(std::ranges::equal(it++->GetVertexes(), std::initializer_list{ 2, 1, 7, 6, 5, 9 }));
			CHECK(std::ranges::equal(it++->GetVertexes(), std::initializer_list{ 4, 10, 11, 12 }));
		}

		AND_THEN("get gamma for different segments")
		{
			CHECK(planar.GetGamma({ 6, 13, 14, 6 }) == 3);
			CHECK(planar.GetGamma({ 6, 13, 5 }) == 2);
			CHECK(planar.GetGamma({ 8, 13, 2 }) == 1);
			CHECK(planar.GetGamma({ 8, 13, 10 }) == 0);
			CHECK(planar.GetGamma({ 13, 1, 13 }) == 0);
		}
	}
}

