#pragma once
#include <vector>
#include <map>
#include "Vertex.h"
#include "Segment.h"
#include <functional>

using EdgesList = std::vector<std::pair<int, int>>;
using Vertexes = std::map<int, Vertex>;

class Graph
{
public:
	Graph(EdgesList const& edgesList);
	Segment PopFirstCycle(Segment segment = {});
	Vertexes GetVertexes() const;
	std::vector<Segment> GetSegments();

private:
	void DeleteSegment(Segment const& segment);
	void BFS(Vertex* prev, Vertex* curr, std::function<void(Vertex*, Segment)> callback, Segment path = {});
	void BuildGraph(EdgesList const& edgesList);

private:
	Vertexes m_vertexes;
};

