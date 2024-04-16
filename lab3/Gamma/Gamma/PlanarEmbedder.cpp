#include "PlanarEmbedder.h"
#include <limits>

PlanarEmbedder::PlanarEmbedder(EdgesList&& edgesList)
	: m_graph(edgesList)
{
}

PlanarGraph PlanarEmbedder::GetPlanarGraph()
{
	m_planar.AddFirstSegment(m_graph.PopFirstCycle());

	while (!m_graph.IsEmpty())
	{
		auto segments = m_graph.GetSegments();
		Segment minGammaSegment = segments.front();
		int minGamma = m_planar.GetGamma(minGammaSegment);
		for (auto& segment : segments)
		{
			int gamma = m_planar.GetGamma(segment);
			if (gamma < minGamma)
			{
				minGammaSegment = segment;
			}
		}

		if (minGamma == 0)
		{
			throw std::runtime_error("graph is not planar");
		}

		m_graph.DeleteSegment(minGammaSegment);
		m_planar.AddSegment(minGammaSegment);
	}

	return m_planar;
}
