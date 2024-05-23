#include "Graph.h"
#include <stdexcept>

Graph::Graph(EdgesList const& edgesList)
{
	BuildGraph(edgesList);
}

Segment Graph::PopFirstCycle()
{
	Vertex* start = std::addressof(m_vertexes.begin()->second);
	Segment cycle = { start->GetNumber() };
	DFS(start, [&](Vertex* curr, Segment path)
		{
			if (path.size() > 2 && curr->GetEdges().contains(start->GetNumber()))
			{
				cycle = path;
			}
		});

	if (cycle.size() == 1)
	{
		throw std::runtime_error("Graph has no cycles");
	}

	auto cycleToDelete = cycle;
	cycleToDelete.push_back(cycle.front());
	DeleteSegment(cycleToDelete);
	return cycle;
}

Vertexes Graph::GetVertexes() const
{
	return m_vertexes;
}

void Graph::DeleteSegment(Segment const& segment)
{
	for (auto& n : segment)
	{
		auto it = m_vertexes.find(n);
		it->second.SetContact();
	}

	EnumEdges(segment, [&](int begin, int end)
		{
			m_vertexes.at(begin).DeleteEdge(end);
		});

	std::erase_if(m_vertexes, [](auto& item)
		{
			return item.second.WithoutLinks();
		});
}

bool Graph::IsEmpty() const
{
	return m_vertexes.empty();
}

std::vector<Segment> Graph::GetSegments()
{
	std::vector<Segment> segments;
	IterateContact([&](auto& it)
		{
			EnumAll([](auto& v) { v.SetVisited(false); });
			Vertex* start = std::addressof(it->second);
			DFS(start, [&](Vertex* curr, Segment path)
				{
					if (curr->IsContact())
					{
						segments.push_back(path);
					}
					else if (path.size() > 2 && curr->GetEdges().contains(start->GetNumber()))
					{
						path.push_back(start->GetNumber());
						segments.push_back(path);
					}
				});
		});

	return segments;
}

void Graph::DFS(Vertex* curr, std::function<void(Vertex*, Segment)> callback, Segment path, Vertex* prev)
{
	path.push_back(curr->GetNumber());
	curr->SetVisited();
	if (prev != nullptr)
	{
		callback(curr, path);
	}
	while (curr->HasNext())
	{
		auto next = curr->Next();
		if (next == prev || next->IsVisited())
		{
			continue;
		}
		DFS(next, callback, path, curr);
	}
}

void Graph::BuildGraph(EdgesList const& edgesList)
{
	for (auto& [first, second] : edgesList)
	{
		auto itFirst = m_vertexes.try_emplace(first, first).first;
		auto itSecond = m_vertexes.try_emplace(second, second).first;
		itFirst->second.AddSibling(std::addressof(itSecond->second));
		itSecond->second.AddSibling(std::addressof(itFirst->second));
	}
}

void Graph::EnumAll(std::function<void(Vertex&)> callback)
{
	for (auto& [_, v] : m_vertexes)
	{
		callback(v);
	}
}

void Graph::IterateContact(std::function<void(Vertexes::iterator&)> callback)
{
	for (auto it = m_vertexes.begin(); it != m_vertexes.end(); ++it)
	{
		if (it->second.IsContact())
		{
			callback(it);
		}
	}
}

void Graph::EnumEdges(Segment const& segment, std::function<void(int begin, int end)> callback)
{
	for (auto first = segment.begin(), second = std::next(first); second != segment.end(); ++first, ++second)
	{
		callback(*first, *second);
	}
}
