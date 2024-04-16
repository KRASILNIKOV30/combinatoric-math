#include "PlanarGraph.h"
#include <stdexcept>
#include <numeric>

PlanarGraph::PlanarGraph(Segment const& segment)
{
	if (!segment.empty())
	{
		AddFirstSegment(segment);
	}
}

void PlanarGraph::AddFirstSegment(Segment const& segment)
{
	m_faces.emplace_back(segment);
	m_faces.emplace_back(Segment(segment.rbegin(), segment.rend()));
}

int PlanarGraph::GetGamma(Segment const& segment) const
{
	return std::reduce(m_faces.begin(), m_faces.end(), 0,
		[&](int n, Face const& face) { return n + face.Contain(segment); });
}

void PlanarGraph::AddSegment(Segment const& segment)
{
	auto it = std::ranges::find_if(m_faces, [&](Face const& face) { return face.Contain(segment); });
	if (it == m_faces.end())
	{
		throw std::runtime_error("Adding segment without contact vertexes");
	}
	m_faces.push_back(it->AddSegment(segment));
}

std::vector<Face> PlanarGraph::GetFaces() const
{
	return m_faces;
}

std::ostream& operator<<(std::ostream& stream, PlanarGraph const& planar)
{
	for (auto& face : planar.GetFaces())
	{
		auto vertexes = face.GetVertexes();
		std::ranges::copy(vertexes, std::ostream_iterator<int>(stream, " "));
		stream << std::endl;
	}

	return stream;
}
