#pragma once
#include <vector>
#include "Face.h"
#include <iostream>

class PlanarGraph
{
public:
	PlanarGraph(Segment const& segment = {});
	void AddFirstSegment(Segment const& segment);
	int GetGamma(Segment const& segment) const;
	void AddSegment(Segment const& segment);
	std::vector<Face> GetFaces() const;
	
private:
	std::vector<Face> m_faces = {};
};

std::ostream& operator<<(std::ostream& stream, PlanarGraph const& planar);
