#pragma once
#include "Graph.h"
#include "PlanarGraph.h"

class PlanarEmbedder
{
public:
	PlanarEmbedder(EdgesList&& edgesList);
	PlanarGraph GetPlanarGraph();

private:
	Graph m_graph;
	PlanarGraph m_planar;
};

