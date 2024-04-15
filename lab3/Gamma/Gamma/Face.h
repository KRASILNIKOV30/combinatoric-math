#pragma once
#include "Segment.h"
#include <functional>

class Face
{
public:
	Face(Segment&& segment);
	Face(Segment const& segment);
	Face AddSegment(Segment const& segment);
	bool Contain(Segment const& segment) const;
	Segment GetVertexes() const;

private:
	Segment GetSegment(Segment const& segment) const;
	void EnumFace(Segment::const_iterator start, Segment::const_iterator end, std::function<void(int)> callback) const;

private:
	Segment m_segment;
};

