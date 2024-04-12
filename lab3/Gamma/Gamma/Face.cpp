#include "Face.h"
#include <stdexcept>

Face::Face(Segment&& segment)
	: m_segment(segment)
{
}

Face Face::AddSegment(Segment const& segment)
{
	Segment newSegment;
	if (segment.front() == segment.back())
	{
		newSegment = std::list(segment.begin(), std::prev(segment.end()));
	}
	else
	{
		newSegment = GetSegment(segment);
	}

	m_segment = GetSegment(std::list(segment.rbegin(), segment.rend()));
	return Face(std::move(newSegment));
}

Segment Face::GetVertexes() const
{
	return m_segment;
}

Segment Face::GetSegment(Segment const& segment) const
{
	Segment face({});

	EnumFace
	(
		std::ranges::find(m_segment, segment.front()),
		std::ranges::find(m_segment, segment.back()),
		[&](int n) { face.push_back(n); }
	);

	face.splice(face.end(), std::list(std::next(segment.begin()), std::prev(segment.end())));

	return face;
}

void Face::EnumFace(Segment::const_iterator start, Segment::const_iterator end, std::function<void(int)> callback) const
{
	bool loop = start == end;
	for (auto& it = start; ; ++it)
	{
		if (it == m_segment.end())
		{
			it = m_segment.begin();
		}

		callback(*it);

		if (it == end)
		{
			if (!loop)
			{
				break;
			}
			loop = false;
		}
	}
}
