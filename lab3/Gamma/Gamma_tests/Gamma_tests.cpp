#include "../../../external/catch2/catch.hpp"
#include "../Gamma/Face.h"

SCENARIO("face tests")
{
	GIVEN("squared face")
	{
		Face face({ 1, 2, 3, 4 });

		WHEN("add segment")
		{
			auto newFace = face.AddSegment({ 1, 3 });

			THEN("face split into two faces")
			{
				CHECK(std::ranges::equal(newFace.GetVertexes(), std::list({ 1, 2, 3 })));
				CHECK(std::ranges::equal(face.GetVertexes(), std::list({ 3, 4, 1 })));
			}
		}
	}

	GIVEN("face")
	{
		Face face({ 1, 2, 3, 4, 5, 6 });

		WHEN("add segment")
		{
			auto newFace = face.AddSegment({ 2, 7, 4 });

			THEN("face split into two faces")
			{
				CHECK(std::ranges::equal(newFace.GetVertexes(), std::list({ 2, 3, 4, 7 })));
				CHECK(std::ranges::equal(face.GetVertexes(), std::list({ 4, 5, 6, 1, 2, 7 })));
			}
		}
	}

	GIVEN("face")
	{
		Face face({ 1, 2, 3, 4 });

		WHEN("add segment")
		{
			auto newFace = face.AddSegment({ 4, 5, 6, 4 });

			THEN("face split into two faces")
			{
				CHECK(std::ranges::equal(newFace.GetVertexes(), std::list({ 4, 5, 6 })));
				CHECK(std::ranges::equal(face.GetVertexes(), std::list({ 4, 1, 2, 3, 4, 6, 5 })));
			}
		}
	}

	GIVEN("face")
	{
		Face face({ 1, 4, 3, 2 });

		WHEN("add segment")
		{
			auto newFace = face.AddSegment({ 4, 5, 6, 4 });

			THEN("face split into two faces")
			{
				CHECK(std::ranges::equal(newFace.GetVertexes(), std::list({ 4, 5, 6 })));
				CHECK(std::ranges::equal(face.GetVertexes(), std::list({ 4, 3, 2, 1, 4, 6, 5 })));
			}
		}
	}

	GIVEN("face")
	{
		Face face({ 1, 5, 2, 4, 3, 2 });

		WHEN("add segment")
		{
			auto newFace = face.AddSegment({ 2, 6, 7, 2 });

			THEN("face split into two faces")
			{
				CHECK(std::ranges::equal(newFace.GetVertexes(), std::list({ 2, 6, 7 })));
				CHECK(std::ranges::equal(face.GetVertexes(), std::list({ 2, 4, 3, 2, 1, 5, 2, 7, 6 })));
			}
		}
	}
}