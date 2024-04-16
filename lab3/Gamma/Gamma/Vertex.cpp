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

void Vertex::SetVisited(bool visited)
{
	if (!visited)
	{
		m_next = 0;
	}

	m_visited = visited;
}

void Vertex::SetContact()
{
	m_contact = true;
}

Edges Vertex::GetEdges()
{
	return m_edges;
}

bool Vertex::WithoutLinks()
{
	return m_edges.empty();
}

void Vertex::DeleteEdge(int vertex)
{
	m_edges.at(vertex)->DeleteLink(m_number);
	DeleteLink(vertex);
}

void Vertex::DeleteLink(int vertex)
{
	m_edges.extract(vertex);
}

