#include "Graph.h"

Graph::Graph(EdgesList const& edgesList)
{
	BuildGraph(edgesList);
}

Segment Graph::PopFirstCycle(Segment segment)
{
	Vertex* start = std::addressof(m_vertexes.begin()->second);
	Segment cycle = { start->GetNumber() };
	BFS(start, [&](Vertex* curr, Segment path)
		{
			if (path.size() > 2 && curr->GetEdges().contains(start->GetNumber()))
			{
				cycle = path;
			}
		});
	DeleteSegment(cycle);
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

	std::erase_if(m_vertexes, [](auto& item)
		{
			return item.second.WillDelete();
		});

	EnumAll([](auto& v) { v.DeleteEdges(); });
}

std::vector<Segment> Graph::GetSegments()
{
	std::vector<Segment> segments;
	IterateContact([&](auto& it)
		{
			EnumAll([](auto& v) { v.SetVisited(false); });
			Vertex* start = std::addressof(it->second);
			BFS(start, [&](Vertex* curr, Segment path)
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

void Graph::BFS(Vertex* curr, std::function<void(Vertex*, Segment)> callback, Segment path, Vertex* prev)
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
		BFS(next, callback, path, curr);
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
