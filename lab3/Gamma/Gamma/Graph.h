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
	void BFS(Vertex* curr, std::function<void(Vertex*, Segment)> callback, Segment path = {}, Vertex* prev = nullptr);
	void BuildGraph(EdgesList const& edgesList);
	void EnumAll(std::function<void(Vertex&)> callback);
	void IterateContact(std::function<void(Vertexes::iterator&)> callback);

private:
	Vertexes m_vertexes;
};

