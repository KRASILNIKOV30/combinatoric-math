#include "Vertex.h"
#include "Segment.h"
#include <algorithm>

int Vertex::GetNumber() const
{
	return m_number;
}

bool Vertex::IsContact() const
{
	return m_contact;
}

bool Vertex::IsVisited() const
{
	return m_visited;
}

void Vertex::AddSibling(Vertex* v)
{
	m_edges[v->GetNumber()] = v;
}

bool Vertex::HasNext() const
{
	return m_next != m_edges.size();
}

Vertex* Vertex::Next()
{
	return std::next(m_edges.begin(), m_next++)->second;
}

void Vertex::SetVisited()
{
	m_visited = true;
}

void Vertex::SetContact()
{
	m_contact = true;
}

Edges Vertex::GetEdges()
{
	return m_edges;
}

bool Vertex::WillDelete()
{
	if (!m_contact)
	{
		return false;
	}

	return std::ranges::all_of(m_edges, [](auto& item)
		{
			return item.second->IsContact();
		}
	);
}

void Vertex::DeleteLink(int vertex)
{
	m_edges.extract(vertex);
}

Vertex::~Vertex()
{
	for (auto& [n, v] : m_edges)
	{
		v->DeleteLink(m_number);
	}
}
