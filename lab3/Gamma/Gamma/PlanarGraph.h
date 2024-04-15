#pragma once
#include <vector>
#include "Face.h"

class PlanarGraph
{
public:
	PlanarGraph(Segment const& segment);
	int GetGammaAccumulate(Segment const& segment) const;
	int GetGammaReduce(Segment const& segment) const;
	int GetGamma(Segment const& segment) const;
	void AddSegment(Segment const& segment);
	std::vector<Face> GetFaces() const;

private:
	std::vector<Face> m_faces;
};

