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
	Segment PopFirstCycle();
	Vertexes GetVertexes() const;
	std::vector<Segment> GetSegments();
	void DeleteSegment(Segment const& segment);
	bool IsEmpty() const;

private:
	void BFS(Vertex* curr, std::function<void(Vertex*, Segment)> callback, Segment path = {}, Vertex* prev = nullptr);
	void BuildGraph(EdgesList const& edgesList);
	void EnumAll(std::function<void(Vertex&)> callback);
	void IterateContact(std::function<void(Vertexes::iterator&)> callback);
	void EnumEdges(Segment const& segment,  std::function<void(int begin, int end)> callback);

private:
	Vertexes m_vertexes;
};
